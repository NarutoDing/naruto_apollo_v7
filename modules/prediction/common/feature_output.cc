/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/prediction/common/feature_output.h"

#include "absl/strings/str_cat.h"
#include "cyber/common/file.h"
#include "modules/common/util/util.h"
#include "modules/prediction/common/prediction_system_gflags.h"

namespace apollo {
namespace prediction {

using apollo::common::TrajectoryPoint;

Features FeatureOutput::features_;
ListDataForLearning FeatureOutput::list_data_for_learning_;
ListPredictionResult FeatureOutput::list_prediction_result_;
ListFrameEnv FeatureOutput::list_frame_env_;
ListDataForTuning FeatureOutput::list_data_for_tuning_;
std::size_t FeatureOutput::idx_feature_ = 0;
std::size_t FeatureOutput::idx_learning_ = 0;
std::size_t FeatureOutput::idx_prediction_result_ = 0;
std::size_t FeatureOutput::idx_frame_env_ = 0;
std::size_t FeatureOutput::idx_tuning_ = 0;
std::mutex FeatureOutput::mutex_feature_;

void FeatureOutput::Close() {
  ADEBUG << "Close feature output";
  switch (FLAGS_prediction_offline_mode) {
    case 1: {
      WriteFeatureProto();
      break;
    }
    case 2: {
      WriteDataForLearning();
      break;
    }
    case 3: {
      WritePredictionResult();
      break;
    }
    case 4: {
      WriteFrameEnv();
      break;
    }
    case 5: {
      WriteDataForTuning();
      break;
    }
    default: {
      // No data dump
      break;
    }
  }
  Clear();
}

void FeatureOutput::Clear() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  idx_feature_ = 0;
  idx_learning_ = 0;
  idx_prediction_result_ = 0;
  idx_frame_env_ = 0;
  idx_tuning_ = 0;
  features_.Clear();
  list_data_for_learning_.Clear();
  list_prediction_result_.Clear();
  list_frame_env_.Clear();
  list_data_for_tuning_.Clear();
}

bool FeatureOutput::Ready() {
  Clear();
  return true;
}

void FeatureOutput::InsertFeatureProto(const Feature& feature) {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  features_.add_feature()->CopyFrom(feature);
}

void FeatureOutput::InsertDataForLearning(
    const Feature& feature, const std::vector<double>& feature_values,
    const std::string& category, const LaneSequence* lane_sequence_ptr) {
  const std::vector<std::string> dummy_string_feature_values;
  InsertDataForLearning(feature, feature_values, dummy_string_feature_values,
                        category, lane_sequence_ptr);
}

void FeatureOutput::InsertDataForLearning(
    const Feature& feature, const std::vector<double>& feature_values,
    const std::vector<std::string>& string_feature_values,
    const std::string& category, const LaneSequence* lane_sequence_ptr) {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  DataForLearning* data_for_learning =
      list_data_for_learning_.add_data_for_learning();
  data_for_learning->set_id(feature.id());
  data_for_learning->set_timestamp(feature.timestamp());
  *(data_for_learning->mutable_features_for_learning()) = {
      feature_values.begin(), feature_values.end()};
  *(data_for_learning->mutable_string_features_for_learning()) = {
      string_feature_values.begin(), string_feature_values.end()};
  data_for_learning->set_category(category);
  ADEBUG << "Insert [" << category
         << "] data for learning with size = " << feature_values.size();
  if (lane_sequence_ptr != nullptr) {
    data_for_learning->set_lane_sequence_id(
        lane_sequence_ptr->lane_sequence_id());
  }
}

void FeatureOutput::InsertPredictionResult(
    const Obstacle* obstacle, const PredictionObstacle& prediction_obstacle,
    const ObstacleConf& obstacle_conf, const Scenario& scenario) {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  PredictionResult* prediction_result =
      list_prediction_result_.add_prediction_result();
  prediction_result->set_id(obstacle->id());
  prediction_result->set_timestamp(prediction_obstacle.timestamp());
  for (int i = 0; i < prediction_obstacle.trajectory_size(); ++i) {
    prediction_result->add_trajectory()->CopyFrom(
        prediction_obstacle.trajectory(i));
    prediction_result->mutable_obstacle_conf()->CopyFrom(obstacle_conf);
  }
  // Insert the scenario that the single obstacle is in
  if (scenario.type() == Scenario::JUNCTION &&
      obstacle->IsInJunction(scenario.junction_id())) {
    prediction_result->mutable_scenario()->set_type(Scenario::JUNCTION);
  } else if (obstacle->IsOnLane()) {
    prediction_result->mutable_scenario()->set_type(Scenario::CRUISE);
  }
}

void FeatureOutput::InsertFrameEnv(const FrameEnv& frame_env) {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  list_frame_env_.add_frame_env()->CopyFrom(frame_env);
}

void FeatureOutput::InsertDataForTuning(
    const Feature& feature, const std::vector<double>& feature_values,
    const std::string& category, const LaneSequence& lane_sequence,
    const std::vector<TrajectoryPoint>& adc_trajectory) {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  DataForTuning* data_for_tuning = list_data_for_tuning_.add_data_for_tuning();
  data_for_tuning->set_id(feature.id());
  data_for_tuning->set_timestamp(feature.timestamp());
  *data_for_tuning->mutable_values_for_tuning() = {feature_values.begin(),
                                                   feature_values.end()};
  data_for_tuning->set_category(category);
  ADEBUG << "Insert [" << category
         << "] data for tuning with size = " << feature_values.size();
  data_for_tuning->set_lane_sequence_id(lane_sequence.lane_sequence_id());
  for (const auto& adc_traj_point : adc_trajectory) {
    data_for_tuning->add_adc_trajectory_point()->CopyFrom(adc_traj_point);
  }
}

void FeatureOutput::WriteFeatureProto() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  if (features_.feature().empty()) {
    ADEBUG << "Skip writing empty feature.";
  } else {
    const std::string file_name = absl::StrCat(
        FLAGS_prediction_data_dir, "/feature.", idx_feature_, ".bin");
    cyber::common::SetProtoToBinaryFile(features_, file_name);
    features_.Clear();
    ++idx_feature_;
  }
}

void FeatureOutput::WriteDataForLearning() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  if (list_data_for_learning_.data_for_learning().empty()) {
    ADEBUG << "Skip writing empty data_for_learning.";
  } else {
    const std::string file_name = absl::StrCat(
        FLAGS_prediction_data_dir, "/datalearn.", idx_learning_, ".bin");
    cyber::common::SetProtoToBinaryFile(list_data_for_learning_, file_name);
    list_data_for_learning_.Clear();
    ++idx_learning_;
  }
}

void FeatureOutput::WritePredictionResult() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  if (list_prediction_result_.prediction_result().empty()) {
    ADEBUG << "Skip writing empty prediction_result.";
  } else {
    const std::string file_name =
        absl::StrCat(FLAGS_prediction_data_dir, "/prediction_result.",
                     idx_prediction_result_, ".bin");
    cyber::common::SetProtoToBinaryFile(list_prediction_result_, file_name);
    list_prediction_result_.Clear();
    ++idx_prediction_result_;
  }
}

void FeatureOutput::WriteFrameEnv() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  if (list_frame_env_.frame_env().empty()) {
    ADEBUG << "Skip writing empty prediction_result.";
  } else {
    const std::string file_name = absl::StrCat(
        FLAGS_prediction_data_dir, "/frame_env.", idx_frame_env_, ".bin");
    cyber::common::SetProtoToBinaryFile(list_frame_env_, file_name);
    list_frame_env_.Clear();
    ++idx_frame_env_;
  }
}

void FeatureOutput::WriteDataForTuning() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  if (list_data_for_tuning_.data_for_tuning().empty()) {
    ADEBUG << "Skip writing empty data_for_tuning.";
    return;
  }
  const std::string file_name = absl::StrCat(
      FLAGS_prediction_data_dir, "/datatuning.", idx_tuning_, ".bin");
  cyber::common::SetProtoToBinaryFile(list_data_for_tuning_, file_name);
  list_data_for_tuning_.Clear();
  ++idx_tuning_;
}

int FeatureOutput::Size() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  return features_.feature_size();
}

int FeatureOutput::SizeOfDataForLearning() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  return list_data_for_learning_.data_for_learning_size();
}

int FeatureOutput::SizeOfPredictionResult() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  return list_prediction_result_.prediction_result_size();
}

int FeatureOutput::SizeOfFrameEnv() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  return list_frame_env_.frame_env_size();
}

int FeatureOutput::SizeOfDataForTuning() {
  UNIQUE_LOCK_MULTITHREAD(mutex_feature_);
  return list_data_for_tuning_.data_for_tuning_size();
}

}  // namespace prediction
}  // namespace apollo
