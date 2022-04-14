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

/**
 * @file
 */

#pragma once

#include "modules/perception/proto/perception_obstacle.pb.h"

/**
 * @namespace apollo::third_party_perception::fusion
 * @brief apollo::third_party_perception
 */
namespace apollo {
namespace third_party_perception {
namespace fusion {

apollo::perception::PerceptionObstacles EyeRadarFusion(
    const apollo::perception::PerceptionObstacles& eye_obstacles,
    const apollo::perception::PerceptionObstacles& radar_obstacles);

}  // namespace fusion
}  // namespace third_party_perception
}  // namespace apollo
