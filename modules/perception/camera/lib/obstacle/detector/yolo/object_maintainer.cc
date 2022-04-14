  /******************************************************************************
 * Copyright 2020 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/perception/camera/lib/obstacle/detector/yolo/object_maintainer.h"

#include "cyber/common/log.h"

namespace apollo {
namespace perception {
namespace camera {

bool ObjectMaintainer::Add(int idx, base::ObjectPtr obj) {
  auto obj_it = assigned_index_.find(idx);
  if (obj_it == assigned_index_.end()) {
    assigned_index_[idx] = obj;
    return true;
  }

  auto prev_obj = obj_it->second;
  const auto &&curr_type = static_cast<int>(obj->sub_type);
  const auto &&prev_type = static_cast<int>(prev_obj->sub_type);

  if (obj->sub_type_probs[curr_type] > prev_obj->sub_type_probs[prev_type]) {
    *prev_obj = *obj;
  }
  return false;
}

}  // namespace camera
}  // namespace perception
}  // namespace apollo
