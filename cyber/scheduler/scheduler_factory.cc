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

#ifndef CYBER_SCHEDULER_SCHEDULER_FACTORY_H_
#define CYBER_SCHEDULER_SCHEDULER_FACTORY_H_

#include "cyber/scheduler/scheduler_factory.h"

#include <atomic>
#include <string>
#include <unordered_map>

#include "cyber/common/environment.h"
#include "cyber/common/file.h"
#include "cyber/common/global_data.h"
#include "cyber/common/util.h"
#include "cyber/scheduler/policy/scheduler_choreography.h"
#include "cyber/scheduler/policy/scheduler_classic.h"
#include "cyber/scheduler/scheduler.h"

namespace apollo {
namespace cyber {
namespace scheduler {

using apollo::cyber::common::GetAbsolutePath;
using apollo::cyber::common::GetProtoFromFile;
using apollo::cyber::common::GlobalData;
using apollo::cyber::common::PathExists;
using apollo::cyber::common::WorkRoot;

namespace {
std::atomic<Scheduler*> instance = {nullptr};
std::mutex mutex;
}  // namespace

Scheduler* Instance() {
  //memory_order_acquire用来修饰一个读操作，表示在本线程中，所有后续的关于此变量
  //的内存操作都必须在本条原子操作完成后执行。
  Scheduler* obj = instance.load(std::memory_order_acquire);
  if (obj == nullptr) {
    std::lock_guard<std::mutex> lock(mutex);
    obj = instance.load(std::memory_order_relaxed);
    if (obj == nullptr) {
      std::string policy("classic");
      std::string conf("conf/");
      conf.append(GlobalData::Instance()->ProcessGroup()).append(".conf");
      //获取绝对路径
      auto cfg_file = GetAbsolutePath(WorkRoot(), conf);
      apollo::cyber::proto::CyberConfig cfg;
      if (PathExists(cfg_file) && GetProtoFromFile(cfg_file, &cfg)) {
        policy = cfg.scheduler_conf().policy();
      } else {
        AWARN << "Scheduler conf named " << cfg_file
              << " not found, use default.";
      }
      if (!policy.compare("classic")) {
        obj = new SchedulerClassic();
      } else if (!policy.compare("choreography")) {
        obj = new SchedulerChoreography();
      } else {
        AWARN << "Invalid scheduler policy: " << policy;
        obj = new SchedulerClassic();
      }
      //memory_order_release：用来修饰一个写操作，表示在本线程中，所有之前的针对该变量的内存操作
      //完成后才能执行本条原子操作。
      instance.store(obj, std::memory_order_release);
    }
  }
  return obj;
}

void CleanUp() {
  Scheduler* obj = instance.load(std::memory_order_acquire);
  if (obj != nullptr) {
    obj->Shutdown();
  }
}

}  // namespace scheduler
}  // namespace cyber
}  // namespace apollo

#endif  // CYBER_SCHEDULER_SCHEDULER_FACTORY_H_
