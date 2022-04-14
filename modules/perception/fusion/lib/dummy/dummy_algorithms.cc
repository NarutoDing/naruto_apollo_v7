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
#include "modules/perception/fusion/lib/dummy/dummy_algorithms.h"

namespace apollo {
namespace perception {
namespace fusion {

// class DummyFusionSystem implementation
bool DummyFusionSystem::Init(const FusionInitOptions& options) {
  main_sensor_ = options.main_sensor;
  return true;
}

bool DummyFusionSystem::Fuse(const FusionOptions& options,
                             const base::FrameConstPtr& sensor_frame,
                             std::vector<base::ObjectPtr>* fused_objects) {
  if (fused_objects == nullptr) {
    return false;
  }

  fused_objects->clear();
  if (sensor_frame->sensor_info.name != main_sensor_) {
    return true;
  }

  fused_objects->resize(sensor_frame->objects.size());
  for (size_t i = 0; i < sensor_frame->objects.size(); i++) {
    (*fused_objects)[i] = sensor_frame->objects[i];
  }
  return true;
}

// class DummyDataAssociation implementation
bool DummyDataAssociation::Init() { return true; }

bool DummyDataAssociation::Associate(const AssociationOptions& options,
                                     SensorFramePtr sensor_measurements,
                                     ScenePtr scene,
                                     AssociationResult* association_result) {
  return true;
}

// class DummyTracker implementation
bool DummyTracker::Init(TrackPtr track, SensorObjectPtr measurement) {
  return true;
}

void DummyTracker::UpdateWithMeasurement(const TrackerOptions& options,
                                         const SensorObjectPtr measurement,
                                         double target_timestamp) {}

void DummyTracker::UpdateWithoutMeasurement(const TrackerOptions& options,
                                            const std::string& sensor_id,
                                            double measurement_timestamp,
                                            double target_timestamp) {}

FUSION_REGISTER_FUSIONSYSTEM(DummyFusionSystem);

}  // namespace fusion
}  // namespace perception
}  // namespace apollo
