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
 **/

#pragma once

#include <memory>
#include <string>

#include "modules/planning/proto/planning_config.pb.h"
#include "modules/planning/tasks/task.h"

namespace apollo {
namespace planning {

class PathDecider : public Task {
 public:
  PathDecider(const TaskConfig &config,
              const std::shared_ptr<DependencyInjector> &injector);

  apollo::common::Status Execute(
      Frame *frame, ReferenceLineInfo *reference_line_info) override;

 private:
  apollo::common::Status Process(const ReferenceLineInfo *reference_line_info,
                                 const PathData &path_data,
                                 PathDecision *const path_decision);

  bool MakeObjectDecision(const PathData &path_data,
                          const std::string &blocking_obstacle_id,
                          PathDecision *const path_decision);

  bool MakeStaticObstacleDecision(const PathData &path_data,
                                  const std::string &blocking_obstacle_id,
                                  PathDecision *const path_decision);

  ObjectStop GenerateObjectStopDecision(const Obstacle &obstacle) const;
};

}  // namespace planning
}  // namespace apollo
