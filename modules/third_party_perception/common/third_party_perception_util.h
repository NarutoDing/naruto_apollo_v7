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
 * @namespace apollo::third_party_perception
 * @brief apollo::third_party_perception
 */

namespace apollo {
namespace third_party_perception {

double GetAngleFromQuaternion(const apollo::common::Quaternion quaternion);

void FillPerceptionPolygon(
    apollo::perception::PerceptionObstacle* const perception_obstacle,
    const double mid_x, const double mid_y, const double mid_z,
    const double length, const double width, const double height,
    const double heading);

// TODO(lizh): change it to PerceptionObstacle::VEHICLE or so
//             when perception obstacle type is extended.
// object type | int
// car         | 0
// truck       | 1
// bike        | 2
// ped         | 3
// unknown     | 4
double GetDefaultObjectLength(const int object_type);

double GetDefaultObjectWidth(const int object_type);

apollo::common::Point3D SLtoXY(const double x, const double y,
                               const double theta);

apollo::common::Point3D SLtoXY(const apollo::common::Point3D& point,
                               const double theta);

double Distance(const apollo::common::Point3D& point1,
                const apollo::common::Point3D& point2);

double Speed(const apollo::common::Point3D& point);

double Speed(const double vx, const double vy);

double GetNearestLaneHeading(const apollo::common::PointENU& point_enu);

double GetNearestLaneHeading(const apollo::common::Point3D& point);

double GetNearestLaneHeading(const double x, const double y, const double z);

double GetLateralDistanceToNearestLane(const apollo::common::Point3D& point);

double HeadingDifference(const double theta1, const double theta2);

}  // namespace third_party_perception
}  // namespace apollo
