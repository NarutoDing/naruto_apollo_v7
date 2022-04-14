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

#include "modules/common/configs/vehicle_config_helper.h"

#include <algorithm>
#include <cmath>

#include "cyber/common/file.h"
#include "modules/common/configs/config_gflags.h"

namespace apollo {
namespace common {

VehicleConfig VehicleConfigHelper::vehicle_config_;
bool VehicleConfigHelper::is_init_ = false;

VehicleConfigHelper::VehicleConfigHelper() {}

void VehicleConfigHelper::Init() { Init(FLAGS_vehicle_config_path); }

void VehicleConfigHelper::Init(const std::string &config_file) {
  //初始化车辆配置文件
  VehicleConfig params;
  ACHECK(cyber::common::GetProtoFromFile(config_file, &params))
      << "Unable to parse vehicle config file " << config_file;
  Init(params);
}

void VehicleConfigHelper::Init(const VehicleConfig &vehicle_params) {
  vehicle_config_ = vehicle_params;
  is_init_ = true;
}

const VehicleConfig &VehicleConfigHelper::GetConfig() {
  if (!is_init_) {
    Init();
  }
  return vehicle_config_;
}

double VehicleConfigHelper::MinSafeTurnRadius() {
  const auto &param = vehicle_config_.vehicle_param();
  double lat_edge_to_center =
      std::max(param.left_edge_to_center(), param.right_edge_to_center());
  double lon_edge_to_center =
      std::max(param.front_edge_to_center(), param.back_edge_to_center());
  return std::sqrt((lat_edge_to_center + param.min_turn_radius()) *
                       (lat_edge_to_center + param.min_turn_radius()) +
                   lon_edge_to_center * lon_edge_to_center);
}

common::math::Box2d VehicleConfigHelper::GetBoundingBox(
    const common::PathPoint &path_point) {
  const auto &vehicle_param = vehicle_config_.vehicle_param();
  double diff_truecenter_and_pointX = (vehicle_param.front_edge_to_center() -
                                       vehicle_param.back_edge_to_center()) /
                                      2.0;
  common::math::Vec2d true_center(
      path_point.x() +
          diff_truecenter_and_pointX * std::cos(path_point.theta()),
      path_point.y() +
          diff_truecenter_and_pointX * std::sin(path_point.theta()));

  return common::math::Box2d(true_center, path_point.theta(),
                             vehicle_param.length(), vehicle_param.width());
}

}  // namespace common
}  // namespace apollo
