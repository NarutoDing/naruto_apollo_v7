/******************************************************************************
 * Copyright 2021 The Apollo Authors. All Rights Reserved.
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
#include <string>
#include <vector>
#include <algorithm>
#include "modules/map/hdmap/hdmap_util.h"
#include "modules/map/pnc_map/path.h"
#include "modules/map/pnc_map/pnc_map.h"
#include "modules/map/proto/map_id.pb.h"
#include "modules/planning/scenarios/scenario.h"

namespace apollo {
namespace planning {
namespace scenario {
namespace deadend_turnaround {

struct DeadEndTurnAroundContext {
  ScenarioDeadEndTurnAroundConfig scenario_config;
  std::string dead_end_id;
  bool pre_stop_rightaway_flag = false;
  hdmap::MapPathPoint pre_stop_rightaway_point;
};

class DeadEndTurnAroundScenario : public Scenario {
 public:
  DeadEndTurnAroundScenario(
    const ScenarioConfig& config,
    const ScenarioContext* context,
    const std::shared_ptr<DependencyInjector>& injector)
      : Scenario(config, context, injector) {}

  void Init() override;

  std::unique_ptr<Stage> CreateStage(
      const ScenarioConfig::StageConfig& stage_config,
      const std::shared_ptr<DependencyInjector>& injector) override;

  static bool IsTransferable(const Frame& frame,
                             const common::PointENU& dead_end_point,
                             const double parking_start_range);

  DeadEndTurnAroundContext* GetContext() { return &context_; }

 private:
  static void RegisterStages();
  bool GetScenarioConfig();
  static bool CheckDistanceToDeadEnd(
        const common::VehicleState& vehicle_state,
        const hdmap::Path& nearby_path,
        const double dead_end_start_range,
        hdmap::JunctionInfoConstPtr* junction);
  static bool SelectTargetDeadEndJunction(
        std::vector<hdmap::JunctionInfoConstPtr>* junctions,
        const apollo::common::PointENU& dead_end_point,
        hdmap::JunctionInfoConstPtr* target_junction);

 private:
  bool init_ = false;
  static apollo::common::util::Factory<
      ScenarioConfig::StageType, Stage,
      Stage* (*)(const ScenarioConfig::StageConfig& stage_config,
                 const std::shared_ptr<DependencyInjector>& injector)>
      s_stage_factory_;
  DeadEndTurnAroundContext context_;
  const hdmap::HDMap* hdmap_ = nullptr;
};

}  // namespace deadend_turnaround
}  // namespace scenario
}  // namespace planning
}  // namespace apollo
