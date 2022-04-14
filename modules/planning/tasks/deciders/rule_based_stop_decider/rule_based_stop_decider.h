/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
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

#pragma once
#include <memory>

#include "modules/planning/common/dependency_injector.h"
#include "modules/planning/proto/planning_config.pb.h"
#include "modules/planning/tasks/deciders/decider.h"

namespace apollo {
namespace planning {

class RuleBasedStopDecider : public Decider {
 public:
  RuleBasedStopDecider(const TaskConfig& config,
                       const std::shared_ptr<DependencyInjector>& injector);

 private:
  apollo::common::Status Process(
      Frame* const frame,
      ReferenceLineInfo* const reference_line_info) override;

  // @brief Rule-based stop at path end
  void AddPathEndStop(Frame* const frame,
                      ReferenceLineInfo* const reference_line_info);

  // @brief Rule-based stop for urgent lane change
  void CheckLaneChangeUrgency(Frame* const frame);

  // @brief Rule-based stop for side pass on reverse lane
  void StopOnSidePass(Frame* const frame,
                      ReferenceLineInfo* const reference_line_info);

  // @brief Check if necessary to set stop fence used for nonscenario side pass
  bool CheckSidePassStop(const PathData& path_data,
                         const ReferenceLineInfo& reference_line_info,
                         double* stop_s_on_pathdata);

  // @brief Set stop fence for side pass
  bool BuildSidePassStopFence(const PathData& path_data,
                              const double stop_s_on_pathdata,
                              common::PathPoint* stop_point, Frame* const frame,
                              ReferenceLineInfo* const reference_line_info);

  // @brief Check if ADV stop at a stop fence
  bool CheckADCStop(const PathData& path_data,
                    const ReferenceLineInfo& reference_line_info,
                    const double stop_s_on_pathdata);

  // @brief Check if needed to check clear again for side pass
  bool CheckClearDone(const ReferenceLineInfo& reference_line_info,
                      const common::PathPoint& stop_point);

 private:
  static constexpr char const* PATH_END_VO_ID_PREFIX = "PATH_END_";
  RuleBasedStopDeciderConfig rule_based_stop_decider_config_;
  bool is_clear_to_change_lane_ = false;
  bool is_change_lane_planning_succeed_ = false;
};
}  // namespace planning
}  // namespace apollo
