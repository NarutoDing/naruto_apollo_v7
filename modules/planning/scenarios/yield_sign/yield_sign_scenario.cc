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

#include "modules/planning/scenarios/yield_sign/yield_sign_scenario.h"

#include "cyber/common/log.h"
#include "modules/perception/proto/perception_obstacle.pb.h"
#include "modules/planning/common/frame.h"
#include "modules/planning/common/planning_context.h"
#include "modules/planning/common/planning_gflags.h"
#include "modules/planning/proto/planning_config.pb.h"
#include "modules/planning/scenarios/yield_sign/stage_approach.h"
#include "modules/planning/scenarios/yield_sign/stage_creep.h"

namespace apollo {
namespace planning {
namespace scenario {
namespace yield_sign {

using apollo::hdmap::HDMapUtil;

using StopSignLaneVehicles =
    std::unordered_map<std::string, std::vector<std::string>>;

apollo::common::util::Factory<
    ScenarioConfig::StageType, Stage,
    Stage* (*)(const ScenarioConfig::StageConfig& stage_config,
               const std::shared_ptr<DependencyInjector>& injector)>
    YieldSignScenario::s_stage_factory_;

void YieldSignScenario::Init() {
  if (init_) {
    return;
  }

  Scenario::Init();

  if (!GetScenarioConfig()) {
    AERROR << "fail to get scenario specific config";
    return;
  }

  const auto& yield_sign_status =
      injector_->planning_context()->planning_status().yield_sign();

  if (yield_sign_status.current_yield_sign_overlap_id().empty()) {
    AERROR << "Could not find yield-sign(s)";
    return;
  }

  context_.current_yield_sign_overlap_ids.clear();
  for (int i = 0; i < yield_sign_status.current_yield_sign_overlap_id_size();
       i++) {
    const std::string yield_sign_overlap_id =
        yield_sign_status.current_yield_sign_overlap_id(i);
    hdmap::YieldSignInfoConstPtr yield_sign =
        HDMapUtil::BaseMap().GetYieldSignById(
            hdmap::MakeMapId(yield_sign_overlap_id));
    if (!yield_sign) {
      AERROR << "Could not find yield sign: " << yield_sign_overlap_id;
    }

    context_.current_yield_sign_overlap_ids.push_back(yield_sign_overlap_id);
  }

  init_ = true;
}

void YieldSignScenario::RegisterStages() {
  if (!s_stage_factory_.Empty()) {
    s_stage_factory_.Clear();
  }
  s_stage_factory_.Register(
      ScenarioConfig::YIELD_SIGN_APPROACH,
      [](const ScenarioConfig::StageConfig& config,
         const std::shared_ptr<DependencyInjector>& injector) -> Stage* {
        return new YieldSignStageApproach(config, injector);
      });
  s_stage_factory_.Register(
      ScenarioConfig::YIELD_SIGN_CREEP,
      [](const ScenarioConfig::StageConfig& config,
         const std::shared_ptr<DependencyInjector>& injector) -> Stage* {
        return new YieldSignStageCreep(config, injector);
      });
}

std::unique_ptr<Stage> YieldSignScenario::CreateStage(
    const ScenarioConfig::StageConfig& stage_config,
    const std::shared_ptr<DependencyInjector>& injector) {
  if (s_stage_factory_.Empty()) {
    RegisterStages();
  }
  auto ptr = s_stage_factory_.CreateObjectOrNull(stage_config.stage_type(),
                                                 stage_config, injector);
  if (ptr) {
    ptr->SetContext(&context_);
  }
  return ptr;
}

/*
 * read scenario specific configs and set in context_ for stages to read
 */
bool YieldSignScenario::GetScenarioConfig() {
  if (!config_.has_yield_sign_config()) {
    AERROR << "miss scenario specific config";
    return false;
  }
  context_.scenario_config.CopyFrom(config_.yield_sign_config());
  return true;
}

}  // namespace yield_sign
}  // namespace scenario
}  // namespace planning
}  // namespace apollo
