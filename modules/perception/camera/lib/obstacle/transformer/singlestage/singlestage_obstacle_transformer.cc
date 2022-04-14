/******************************************************************************
 * Copyright 2020 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#include "modules/perception/camera/lib/obstacle/transformer/singlestage/singlestage_obstacle_transformer.h"

#include <limits>

#include "cyber/common/file.h"
#include "cyber/common/log.h"
#include "modules/perception/camera/common/global_config.h"

namespace apollo {
namespace perception {
namespace camera {

void TransformerParams::set_default() {
  max_nr_iter = 10;
  learning_rate = 0.7f;
  k_min_cost = 4 * sqrtf(2.0f);
  eps_cost = 1e-5f;
}

bool SingleStageObstacleTransformer::Init(
    const ObstacleTransformerInitOptions &options) {
  std::string transformer_config =
      cyber::common::GetAbsolutePath(options.root_dir, options.conf_file);

  if (!cyber::common::GetProtoFromFile(transformer_config,
                                      &singlestage_param_)) {
    AERROR << "Read config failed: " << transformer_config;
    return false;
  }
  AINFO << "Load transformer parameters from " << transformer_config
        << " \nmin dimension: " << singlestage_param_.min_dimension_val()
        << " \ndo template search: " << singlestage_param_.check_dimension();

  // Init object template
  object_template_manager_ = ObjectTemplateManager::Instance();

  return true;
}

int SingleStageObstacleTransformer::MatchTemplates(
    base::ObjectSubType sub_type, float *dimension_hwl) {
  const TemplateMap &kMinTemplateHWL =
      object_template_manager_->MinTemplateHWL();
  const TemplateMap &kMidTemplateHWL =
      object_template_manager_->MidTemplateHWL();
  const TemplateMap &kMaxTemplateHWL =
      object_template_manager_->MaxTemplateHWL();

  int type_min_vol_index = 0;
  float min_dimension_val =
      std::min(std::min(dimension_hwl[0], dimension_hwl[1]), dimension_hwl[2]);

  const std::map<TemplateIndex, int> &kLookUpTableMinVolumeIndex =
      object_template_manager_->LookUpTableMinVolumeIndex();

  switch (sub_type) {
    case base::ObjectSubType::TRAFFICCONE: {
      const float *min_tmplt_cur_type = kMinTemplateHWL.at(sub_type).data();
      const float *max_tmplt_cur_type = kMaxTemplateHWL.at(sub_type).data();
      dimension_hwl[0] = std::min(dimension_hwl[0], max_tmplt_cur_type[0]);
      dimension_hwl[0] = std::max(dimension_hwl[0], min_tmplt_cur_type[0]);
      break;
    }
    case base::ObjectSubType::PEDESTRIAN:
    case base::ObjectSubType::CYCLIST:
    case base::ObjectSubType::MOTORCYCLIST: {
      const float *min_tmplt_cur_type = kMinTemplateHWL.at(sub_type).data();
      const float *mid_tmplt_cur_type = kMidTemplateHWL.at(sub_type).data();
      const float *max_tmplt_cur_type = kMaxTemplateHWL.at(sub_type).data();
      float dh_min = fabsf(dimension_hwl[0] - min_tmplt_cur_type[0]);
      float dh_mid = fabsf(dimension_hwl[0] - mid_tmplt_cur_type[0]);
      float dh_max = fabsf(dimension_hwl[0] - max_tmplt_cur_type[0]);
      std::vector<std::pair<float, float>> diff_hs;
      diff_hs.push_back(std::make_pair(dh_min, min_tmplt_cur_type[0]));
      diff_hs.push_back(std::make_pair(dh_mid, mid_tmplt_cur_type[0]));
      diff_hs.push_back(std::make_pair(dh_max, max_tmplt_cur_type[0]));
      sort(diff_hs.begin(), diff_hs.end(),
           [](const std::pair<float, float> &a,
              const std::pair<float, float> &b) -> bool {
             return a.first < b.first;
           });
      dimension_hwl[0] = diff_hs[0].second;
      break;
    }
    case base::ObjectSubType::CAR:
      type_min_vol_index =
          kLookUpTableMinVolumeIndex.at(TemplateIndex::CAR_MIN_VOLUME_INDEX);
      break;
    case base::ObjectSubType::VAN:
      type_min_vol_index =
          kLookUpTableMinVolumeIndex.at(TemplateIndex::VAN_MIN_VOLUME_INDEX);
      break;
    case base::ObjectSubType::TRUCK:
      type_min_vol_index =
          kLookUpTableMinVolumeIndex.at(TemplateIndex::TRUCK_MIN_VOLUME_INDEX);
      break;
    case base::ObjectSubType::BUS:
      type_min_vol_index =
          kLookUpTableMinVolumeIndex.at(TemplateIndex::BUS_MIN_VOLUME_INDEX);
      break;
    default:
      if (min_dimension_val < singlestage_param_.min_dimension_val()) {
        common::IScale3(dimension_hwl, singlestage_param_.min_dimension_val() *
                                           common::IRec(min_dimension_val));
      }
      break;
  }
  return type_min_vol_index;
}

void SingleStageObstacleTransformer::FillResults(
    float object_center[3], float dimension_hwl[3], float rotation_y,
    Eigen::Affine3d camera2world_pose, float theta_ray, base::ObjectPtr obj) {
  if (obj == nullptr) {
    return;
  }
  object_center[1] -= dimension_hwl[0] / 2;
  obj->camera_supplement.local_center(0) = object_center[0];
  obj->camera_supplement.local_center(1) = object_center[1];
  obj->camera_supplement.local_center(2) = object_center[2];
  ADEBUG << "Obj id: " << obj->track_id;
  ADEBUG << "Obj type: " << static_cast<int>(obj->sub_type);
  ADEBUG << "Obj ori dimension: " << obj->size[2] << ", " << obj->size[1]
         << ", " << obj->size[0];
  obj->center(0) = static_cast<double>(object_center[0]);
  obj->center(1) = static_cast<double>(object_center[1]);
  obj->center(2) = static_cast<double>(object_center[2]);
  obj->center = camera2world_pose * obj->center;

  obj->size(2) = dimension_hwl[0];
  obj->size(1) = dimension_hwl[1];
  obj->size(0) = dimension_hwl[2];

  obj->center_uncertainty(0) = static_cast<float>(0);
  obj->center_uncertainty(1) = static_cast<float>(0);
  obj->center_uncertainty(2) = static_cast<float>(0);

  float theta = rotation_y;
  Eigen::Vector3d dir = (camera2world_pose.matrix().block(0, 0, 3, 3) *
                         Eigen::Vector3d(cos(theta), 0, -sin(theta)));
  obj->direction[0] = static_cast<float>(dir[0]);
  obj->direction[1] = static_cast<float>(dir[1]);
  obj->direction[2] = static_cast<float>(dir[2]);
  obj->theta = static_cast<float>(atan2(dir[1], dir[0]));
  obj->theta_variance = static_cast<float>(1.0);

  obj->camera_supplement.alpha = rotation_y - theta_ray;

  ADEBUG << "Dimension hwl: " << dimension_hwl[0] << ", " << dimension_hwl[1]
         << ", " << dimension_hwl[2];
  ADEBUG << "Obj ry:" << rotation_y;
  ADEBUG << "Obj theta: " << obj->theta;
  ADEBUG << "Obj center from transformer: " << obj->center.transpose();
}

bool SingleStageObstacleTransformer::Transform(
    const ObstacleTransformerOptions &options, CameraFrame *frame) {
  if (frame->detected_objects.empty()) {
    ADEBUG << "No object input to transformer.";
    return true;
  }

  const auto &camera_k_matrix = frame->camera_k_matrix;
  float k_mat[9] = {0};
  for (size_t i = 0; i < 3; i++) {
    size_t i3 = i * 3;
    for (size_t j = 0; j < 3; j++) {
      k_mat[i3 + j] = camera_k_matrix(i, j);
    }
  }
  ADEBUG << "Camera k matrix input to transformer: \n"
         << k_mat[0] << ", " << k_mat[1] << ", " << k_mat[2] << "\n"
         << k_mat[3] << ", " << k_mat[4] << ", " << k_mat[5] << "\n"
         << k_mat[6] << ", " << k_mat[7] << ", " << k_mat[8] << "\n";
  const auto &camera2world_pose = frame->camera2world_pose;

  int height = frame->data_provider->src_height();
  int width = frame->data_provider->src_width();
  int nr_transformed_obj = 0;
  const float PI = common::Constant<float>::PI();
  for (auto &obj : frame->detected_objects) {
    if (obj == nullptr) {
      ADEBUG << "Empty object input to transformer.";
      continue;
    }

    // set object mapper options
    float theta_ray = atan2(obj->camera_supplement.local_center[0],
                           obj->camera_supplement.local_center[2]);

    // process
    float object_center[3] = {obj->camera_supplement.local_center[0],
                              obj->camera_supplement.local_center[1],
                              obj->camera_supplement.local_center[2]};
    float dimension_hwl[3] = {obj->size(2), obj->size(1), obj->size(0)};
    float rotation_y =
              theta_ray + static_cast<float>(obj->camera_supplement.alpha);
    if (rotation_y < -PI) {
      rotation_y += 2 * PI;
    } else if (rotation_y >= PI) {
      rotation_y -= 2 * PI;
    }

    // adjust center point
    float bbox[4] = {0};
    bbox[0] = obj->camera_supplement.box.xmin;
    bbox[1] = obj->camera_supplement.box.ymin;
    bbox[2] = obj->camera_supplement.box.xmax;
    bbox[3] = obj->camera_supplement.box.ymax;
    float center2d[3] = {0};

    CenterPointFromBbox(bbox, dimension_hwl, rotation_y, object_center,
                        center2d, k_mat, height, width);
    // fill back results
    FillResults(object_center, dimension_hwl, rotation_y, camera2world_pose,
                theta_ray, obj);

    ++nr_transformed_obj;
  }
  return nr_transformed_obj > 0;
}

float SingleStageObstacleTransformer::CenterPointFromBbox(const float *bbox,
                                                          const float *hwl,
                                                          float ry,
                                                          float *center,
                                                          float *center_2d,
                                                          const float* k_mat,
                                                          int height,
                                                          int width) {
  float height_bbox = bbox[3] - bbox[1];
  float width_bbox = bbox[2] - bbox[0];
  if (width_bbox <= 0.0f || height_bbox <= 0.0f) {
    AERROR << "Check predict bounding box, width or height is 0";
    return false;
  }

  float f = (k_mat[0] + k_mat[4]) / 2;
  float depth = f * hwl[0] * common::IRec(height_bbox);

  // Compensate from the nearest vertical edge to center
  const float PI = common::Constant<float>::PI();
  float theta_bbox = static_cast<float>(atan(hwl[1] * common::IRec(hwl[2])));
  float radius_bbox =
      common::ISqrt(common::ISqr(hwl[2] / 2) + common::ISqr(hwl[1] / 2));

  float abs_ry = fabsf(ry);
  float theta_z = std::min(abs_ry, PI - abs_ry) + theta_bbox;
  theta_z = std::min(theta_z, PI - theta_z);
  depth += static_cast<float>(fabs(radius_bbox * sin(theta_z)));

  // Back-project to solve center
  float location[3] = {center[0], center[1] - hwl[0]/2, center[2]};
  common::IProjectThroughIntrinsic(k_mat, location, center_2d);
  center_2d[0] *= common::IRec(center_2d[2]);
  center_2d[1] *= common::IRec(center_2d[2]);
  if (fabsf(depth - center[2]) * common::IRec(center[2]) > 0.1) {
    ConstraintCenterPoint(bbox, center[2], ry, hwl, k_mat,
                          center, center_2d, height, width);
  }
  return depth;
}

void SingleStageObstacleTransformer::ConstraintCenterPoint(const float *bbox,
                                                           const float &z_ref,
                                                           const float &ry,
                                                           const float *hwl,
                                                           const float *k_mat,
                                                           float *center,
                                                           float *x,
                                                           int height,
                                                           int width) {
  float center_2d_target[2] =
                {(bbox[0] + bbox[2]) / 2, (bbox[1] + bbox[3]) / 2};
  const float K_MIN_COST = params_.k_min_cost;
  const float EPS_COST_DELTA = params_.eps_cost;
  const float LEARNING_RATE = params_.learning_rate;
  const int MAX_ITERATION = params_.max_nr_iter;

  float cost_pre = 2.0f * static_cast<float>(width);
  float cost_delta = 0.0f;
  float center_temp[3] = {0};
  float rot_y[9] = {0};

  // Get rotation matrix rot_y
  /*
      cos(ry)   0   sin(ry)
  R =    0      1     0  
      -sin(ry)  0   cos(ry)
  */
  GenRotMatrix(ry, rot_y);

  int iter = 1;
  bool stop = false;
  float h = hwl[0];
  float w = hwl[1];
  float l = hwl[2];
  float x_corners[8] = {0};
  float y_corners[8] = {0};
  float z_corners[8] = {0};

  float x_upper_bound = static_cast<float>(width - 1);
  float y_upper_bound = static_cast<float>(height - 1);

  // Get dimension matrix
  /*
      l/2  l/2  -l/2  -l/2  l/2  l/2  -l/2  -l/2
  D =  0    0     0     0    -h   -h    -h    -h
      w/2  -w/2 -w/2   w/2  w/2  -w/2 -w/2  -w/2
  */
  GenCorners(h, w, l, x_corners, y_corners, z_corners);
  while (!stop) {
    // Back project 3D center from image x and depth z_ref to camera center_temp
    common::IBackprojectCanonical(x, k_mat, z_ref, center_temp);
    // From center to location
    center_temp[1] += hwl[0] / 2;
    float x_min = std::numeric_limits<float>::max();
    float x_max = -std::numeric_limits<float>::max();
    float y_min = std::numeric_limits<float>::max();
    float y_max = -std::numeric_limits<float>::max();
    float x_images[3] = {0};

    for (int i = 0; i < 8; ++i) {
      // Bbox from x_images
      float x_box[3] = {x_corners[i], y_corners[i], z_corners[i]};
      common::IProjectThroughKRt(k_mat, rot_y, center_temp, x_box, x_images);
      x_images[0] *= common::IRec(x_images[2]);
      x_images[1] *= common::IRec(x_images[2]);
      x_min = std::min(x_min, x_images[0]);
      x_max = std::max(x_max, x_images[0]);
      y_min = std::min(y_min, x_images[1]);
      y_max = std::max(y_max, x_images[1]);
    }

    // Clamp bounding box from 0~boundary
    x_min = std::min(std::max(x_min, 0.0f), x_upper_bound);
    x_max = std::min(std::max(x_max, 0.0f), x_upper_bound);
    y_min = std::min(std::max(y_min, 0.0f), y_upper_bound);
    y_max = std::min(std::max(y_max, 0.0f), y_upper_bound);

    // Calculate 2D center point and get cost
    // cost = (center_gt - center_cal)**2
    float center_cur[2] = {(x_min + x_max) / 2, (y_min + y_max) / 2};
    float cost_cur = common::ISqrt(
                     common::ISqr(center_cur[0] - center_2d_target[0]) +
                     common::ISqr(center_cur[1] - center_2d_target[1]));

    // Stop or continue
    if (cost_cur >= cost_pre) {
      stop = true;
    } else {
      memcpy(center, center_temp, sizeof(float) * 3);
      cost_delta = (cost_pre - cost_cur) / cost_pre;
      cost_pre = cost_cur;
      // Update 2D center point by descent method
      x[0] += (center_2d_target[0] - center_cur[0]) * LEARNING_RATE;
      x[1] += (center_2d_target[1] - center_cur[1]) * LEARNING_RATE;
      ++iter;
      // Termination condition
      stop = iter >= MAX_ITERATION || cost_delta < EPS_COST_DELTA ||
             cost_pre < K_MIN_COST;
    }
  }
}

std::string SingleStageObstacleTransformer::Name() const {
  return "SingleStageObstacleTransformer";
}

// Register plugin.
REGISTER_OBSTACLE_TRANSFORMER(SingleStageObstacleTransformer);

}  // namespace camera
}  // namespace perception
}  // namespace apollo
