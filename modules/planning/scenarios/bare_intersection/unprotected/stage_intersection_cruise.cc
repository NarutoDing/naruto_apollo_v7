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

/**
 * @file
 **/

#include "modules/planning/scenarios/bare_intersection/unprotected/stage_intersection_cruise.h"

#include <memory>

#include "cyber/common/log.h"

namespace apollo {
namespace planning {
namespace scenario {
namespace bare_intersection {

Stage::StageStatus BareIntersectionUnprotectedStageIntersectionCruise::Process(
    const common::TrajectoryPoint& planning_init_point, Frame* frame) {
  ADEBUG << "stage: IntersectionCruise";
  CHECK_NOTNULL(frame);

  bool plan_ok = ExecuteTaskOnReferenceLine(planning_init_point, frame);
  if (!plan_ok) {
    AERROR << "StopSignUnprotectedStageIntersectionCruise plan error";
  }

  bool stage_done = stage_impl_.CheckDone(
      *frame, ScenarioConfig::BARE_INTERSECTION_UNPROTECTED, config_,
      injector_->planning_context(), false);
  if (stage_done) {
    return FinishStage();
  }
  return Stage::RUNNING;
}

Stage::StageStatus
BareIntersectionUnprotectedStageIntersectionCruise::FinishStage() {
  return FinishScenario();
}

}  // namespace bare_intersection
}  // namespace scenario
}  // namespace planning
}  // namespace apollo
