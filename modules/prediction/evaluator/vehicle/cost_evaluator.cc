/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
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

#include "modules/prediction/evaluator/vehicle/cost_evaluator.h"
#include "modules/prediction/common/prediction_util.h"

namespace apollo {
namespace prediction {

CostEvaluator::CostEvaluator() {
  evaluator_type_ = ObstacleConf::COST_EVALUATOR;
}

bool CostEvaluator::Evaluate(Obstacle* obstacle_ptr,
                             ObstaclesContainer* obstacles_container) {
  CHECK_NOTNULL(obstacle_ptr);

  obstacle_ptr->SetEvaluatorType(evaluator_type_);

  int id = obstacle_ptr->id();
  if (!obstacle_ptr->latest_feature().IsInitialized()) {
    AERROR << "Obstacle [" << id << "] has no latest feature.";
    return false;
  }

  Feature* latest_feature_ptr = obstacle_ptr->mutable_latest_feature();
  CHECK_NOTNULL(latest_feature_ptr);
  if (!latest_feature_ptr->has_lane() ||
      !latest_feature_ptr->lane().has_lane_graph()) {
    ADEBUG << "Obstacle [" << id << "] has no lane graph.";
    return false;
  }

  double obstacle_length = 0.0;
  if (latest_feature_ptr->has_length()) {
    obstacle_length = latest_feature_ptr->length();
  }
  double obstacle_width = 0.0;
  if (latest_feature_ptr->has_width()) {
    obstacle_width = latest_feature_ptr->width();
  }

  LaneGraph* lane_graph_ptr =
      latest_feature_ptr->mutable_lane()->mutable_lane_graph();
  CHECK_NOTNULL(lane_graph_ptr);
  if (lane_graph_ptr->lane_sequence().empty()) {
    AERROR << "Obstacle [" << id << "] has no lane sequences.";
    return false;
  }

  for (int i = 0; i < lane_graph_ptr->lane_sequence_size(); ++i) {
    LaneSequence* lane_sequence_ptr = lane_graph_ptr->mutable_lane_sequence(i);
    CHECK_NOTNULL(lane_sequence_ptr);
    double probability =
        ComputeProbability(obstacle_length, obstacle_width, *lane_sequence_ptr);
    lane_sequence_ptr->set_probability(probability);
  }
  return true;
}

double CostEvaluator::ComputeProbability(const double obstacle_length,
                                         const double obstacle_width,
                                         const LaneSequence& lane_sequence) {
  double front_lateral_distance_cost =
      FrontLateralDistanceCost(obstacle_length, obstacle_width, lane_sequence);
  return apollo::common::math::Sigmoid(front_lateral_distance_cost);
}

double CostEvaluator::FrontLateralDistanceCost(
    const double obstacle_length, const double obstacle_width,
    const LaneSequence& lane_sequence) {
  if (lane_sequence.lane_segment().empty() ||
      lane_sequence.lane_segment(0).lane_point().empty()) {
    AWARN << "Empty lane sequence.";
    return 0.0;
  }
  const LanePoint& lane_point = lane_sequence.lane_segment(0).lane_point(0);
  double lane_l = -lane_point.relative_l();
  double distance = std::abs(lane_l - obstacle_length / 2.0 *
                                          std::sin(lane_point.angle_diff()));
  double half_lane_width = lane_point.width() / 2.0;
  return half_lane_width - distance;
}

}  // namespace prediction
}  // namespace apollo
