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

#pragma once

#include <memory>

#include "modules/planning/scenarios/scenario.h"

namespace apollo {
namespace planning {
namespace scenario {
namespace narrow_street_u_turn {

class NarrowStreetUTurnScenario : public Scenario {
 public:
  NarrowStreetUTurnScenario(const ScenarioConfig& config,
                            const ScenarioContext* context,
                            const std::shared_ptr<DependencyInjector>& injector)
      : Scenario(config, context, injector) {}

  std::unique_ptr<Stage> CreateStage(
      const ScenarioConfig::StageConfig& stage_config,
      const std::shared_ptr<DependencyInjector>& injector) override;
};

}  // namespace narrow_street_u_turn
}  // namespace scenario
}  // namespace planning
}  // namespace apollo
