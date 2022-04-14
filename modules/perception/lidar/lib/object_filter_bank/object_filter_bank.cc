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
#include "modules/perception/lidar/lib/object_filter_bank/object_filter_bank.h"

#include "cyber/common/file.h"
#include "modules/perception/lib/config_manager/config_manager.h"
#include "modules/perception/lidar/common/lidar_log.h"
#include "modules/perception/lidar/lib/object_filter_bank/proto/filter_bank_config.pb.h"

namespace apollo {
namespace perception {
namespace lidar {

using apollo::cyber::common::GetAbsolutePath;

bool ObjectFilterBank::Init(const ObjectFilterInitOptions& options) {
  auto config_manager = lib::ConfigManager::Instance();
  const lib::ModelConfig* model_config = nullptr;
  ACHECK(config_manager->GetModelConfig(Name(), &model_config));
  const std::string work_root = config_manager->work_root();
  std::string config_file;
  std::string root_path;
  ACHECK(model_config->get_value("root_path", &root_path));
  config_file = GetAbsolutePath(work_root, root_path);
  config_file = GetAbsolutePath(config_file, options.sensor_name);
  config_file = GetAbsolutePath(config_file, "filter_bank.conf");
  FilterBankConfig config;
  ACHECK(apollo::cyber::common::GetProtoFromFile(config_file, &config));
  filter_bank_.clear();
  for (int i = 0; i < config.filter_name_size(); ++i) {
    const auto& name = config.filter_name(i);
    BaseObjectFilter* filter =
        BaseObjectFilterRegisterer::GetInstanceByName(name);
    if (!filter) {
      AINFO << "Failed to find object filter: " << name << ", skipped";
      continue;
    }
    if (!filter->Init()) {
      AINFO << "Failed to init object filter: " << name << ", skipped";
      continue;
    }
    filter_bank_.push_back(filter);
    AINFO << "Filter bank add filter: " << name;
  }
  return true;
}

bool ObjectFilterBank::Filter(const ObjectFilterOptions& options,
                              LidarFrame* frame) {
  size_t object_number = frame->segmented_objects.size();
  for (auto& filter : filter_bank_) {
    if (!filter->Filter(options, frame)) {
      AINFO << "Failed to filter objects in: " << filter->Name();
    }
  }
  AINFO << "Object filter bank, filtered objects size: from " << object_number
        << " to " << frame->segmented_objects.size();
  return true;
}

}  // namespace lidar
}  // namespace perception
}  // namespace apollo
