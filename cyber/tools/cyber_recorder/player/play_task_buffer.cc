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

#include "cyber/tools/cyber_recorder/player/play_task_buffer.h"

#include <utility>

namespace apollo {
namespace cyber {
namespace record {

PlayTaskBuffer::PlayTaskBuffer() {}

PlayTaskBuffer::~PlayTaskBuffer() { tasks_.clear(); }

size_t PlayTaskBuffer::Size() const {
  std::lock_guard<std::mutex> lck(mutex_);
  return tasks_.size();
}

bool PlayTaskBuffer::Empty() const {
  std::lock_guard<std::mutex> lck(mutex_);
  return tasks_.empty();
}

void PlayTaskBuffer::Push(const TaskPtr& task) {
  if (task == nullptr) {
    return;
  }
  std::lock_guard<std::mutex> lck(mutex_);
  tasks_.insert(std::make_pair(task->msg_play_time_ns(), task));
}

PlayTaskBuffer::TaskPtr PlayTaskBuffer::Front() {
  std::lock_guard<std::mutex> lck(mutex_);
  if (tasks_.empty()) {
    return nullptr;
  }
  auto res = tasks_.begin()->second;
  return res;
}

void PlayTaskBuffer::PopFront() {
  std::lock_guard<std::mutex> lck(mutex_);
  if (!tasks_.empty()) {
    tasks_.erase(tasks_.begin());
  }
}

}  // namespace record
}  // namespace cyber
}  // namespace apollo
