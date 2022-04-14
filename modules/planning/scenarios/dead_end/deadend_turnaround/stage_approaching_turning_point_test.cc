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
#include "modules/planning/scenarios/dead_end/deadend_turnaround/stage_approaching_turning_point.h"

#include "gtest/gtest.h"
#include "modules/planning/proto/planning_config.pb.h"

namespace apollo {
namespace planning {
namespace scenario {
namespace deadend_turnaround {
class StageApproachingTurningPointTest : public ::testing::Test {
 public:
  virtual void SetUp() {
    config_.set_stage_type(
        ScenarioConfig::DEADEND_TURNAROUND_APPROACHING_TURNING_POINT);
    injector_ = std::make_shared<DependencyInjector>();
  }

 protected:
  ScenarioConfig::StageConfig config_;
  std::shared_ptr<DependencyInjector> injector_;
};

TEST_F(StageApproachingTurningPointTest, Init) {
  StageApproachingTurningPoint stage_approaching_turning_point(config_,
                                                             injector_);
  EXPECT_EQ(stage_approaching_turning_point.Name(),
            ScenarioConfig::StageType_Name(
                ScenarioConfig::DEADEND_TURNAROUND_APPROACHING_TURNING_POINT));
}

}  // namespace deadend_turnaround
}  // namespace scenario
}  // namespace planning
}  // namespace apollo
