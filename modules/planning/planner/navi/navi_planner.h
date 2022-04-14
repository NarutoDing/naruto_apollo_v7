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

/**
 * @file
 * @brief This file provides the declaration of the class "NaviPlanner".
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "modules/common/proto/pnc_point.pb.h"
#include "modules/common/status/status.h"
#include "modules/common/util/factory.h"
#include "modules/planning/common/reference_line_info.h"
#include "modules/planning/math/curve1d/quintic_polynomial_curve1d.h"
#include "modules/planning/navi/decider/navi_task.h"
#include "modules/planning/planner/planner.h"
#include "modules/planning/proto/planning.pb.h"
#include "modules/planning/proto/planning_config.pb.h"
#include "modules/planning/reference_line/reference_line.h"
#include "modules/planning/reference_line/reference_point.h"

/**
 * @namespace apollo::planning
 * @brief apollo::planning
 */
namespace apollo {
namespace planning {

/**
 * @class NaviPlanner
 * @brief NaviPlanner is a planner based on real-time relative maps. It uses the
 * vehicle's FLU (Front-Left-Up) coordinate system to accomplish tasks such as
 * cruising, following, overtaking, nudging, changing lanes and stopping.
 * Note that NaviPlanner is only used in navigation mode (turn on navigation
 * mode by setting "FLAGS_use_navigation_mode" to "true") and do not use it in
 * standard mode.
 */
class NaviPlanner : public PlannerWithReferenceLine {
 public:
  NaviPlanner() = delete;
  explicit NaviPlanner(const std::shared_ptr<DependencyInjector>& injector)
      : PlannerWithReferenceLine(injector) {}

  virtual ~NaviPlanner() = default;

  std::string Name() override { return "NAVI"; }

  common::Status Init(const PlanningConfig& config) override;

  /**
   * @brief Override function Plan in parent class Planner.
   * @param planning_init_point The trajectory point where planning starts.
   * @param frame Current planning frame.
   * @return OK if planning succeeds; error otherwise.
   */
  common::Status Plan(const common::TrajectoryPoint& planning_init_point,
                      Frame* frame,
                      ADCTrajectory* ptr_computed_trajectory) override;

  void Stop() override {}

  /**
   * @brief Override function Plan in parent class Planner.
   * @param planning_init_point The trajectory point where planning starts.
   * @param frame Current planning frame.
   * @param reference_line_info The computed reference line.
   * @return OK if planning succeeds; error otherwise.
   */
  common::Status PlanOnReferenceLine(
      const common::TrajectoryPoint& planning_init_point, Frame* frame,
      ReferenceLineInfo* reference_line_info) override;

 private:
  void RegisterTasks();
  std::vector<common::SpeedPoint> GenerateInitSpeedProfile(
      const common::TrajectoryPoint& planning_init_point,
      const ReferenceLineInfo* reference_line_info);

  std::vector<common::SpeedPoint> DummyHotStart(
      const common::TrajectoryPoint& planning_init_point);

  std::vector<common::SpeedPoint> GenerateSpeedHotStart(
      const common::TrajectoryPoint& planning_init_point);

  void GenerateFallbackPathProfile(const ReferenceLineInfo* reference_line_info,
                                   PathData* path_data);

  void GenerateFallbackSpeedProfile(SpeedData* speed_data);

  SpeedData GenerateStopProfile(const double init_speed,
                                const double init_acc) const;

  SpeedData GenerateStopProfileFromPolynomial(const double init_speed,
                                              const double init_acc) const;

  bool IsValidProfile(const QuinticPolynomialCurve1d& curve) const;

  void RecordObstacleDebugInfo(ReferenceLineInfo* reference_line_info);

  void RecordDebugInfo(ReferenceLineInfo* reference_line_info,
                       const std::string& name, const double time_diff_ms);

 private:
  apollo::common::util::Factory<TaskConfig::TaskType, NaviTask> task_factory_;
  std::vector<std::unique_ptr<NaviTask>> tasks_;
};

}  // namespace planning
}  // namespace apollo
