/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
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
#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include <boost/circular_buffer.hpp>

#include "modules/perception/base/image_8u.h"
#include "modules/perception/base/traffic_light.h"
#include "modules/perception/camera/lib/traffic_light/preprocessor/multi_camera_projection.h"
#include "modules/perception/camera/lib/traffic_light/preprocessor/pose.h"

#include "modules/perception/camera/common/camera_frame.h"
#include "modules/perception/camera/lib/interface/base_init_options.h"
#include "modules/perception/camera/lib/interface/base_tl_preprocessor.h"
#include "modules/perception/lib/registerer/registerer.h"

namespace apollo {
namespace perception {
namespace camera {

class TLPreprocessor : public BaseTLPreprocessor {
 public:
  TLPreprocessor() = default;
  ~TLPreprocessor() = default;

  bool Init(const TrafficLightPreprocessorInitOptions& options) override;

  std::string Name() const override;

  bool UpdateCameraSelection(const CarPose& pose,
                    const TLPreprocessorOption& option,
                    std::vector<base::TrafficLightPtr>* lights) override;

  bool SyncInformation(const double ts, const std::string& camera_name);
  bool UpdateLightsProjection(const CarPose& pose,
                    const TLPreprocessorOption& option,
                    const std::string& camera_name,
                    std::vector<base::TrafficLightPtr>* lights) override;

  bool SetCameraWorkingFlag(const std::string& camera_name,
                    bool is_working) override;
  bool GetCameraWorkingFlag(const std::string& camera_name,
                            bool* is_working) const override;

  const std::vector<std::string>&
    GetCameraNamesByDescendingFocalLen() const override {
    return projection_.getCameraNamesByDescendingFocalLen();
  }
  bool GetAlllightsOutsideFlag() const;

 private:
  void SelectCamera(
      std::vector<base::TrafficLightPtrs>* lights_on_image_array,
      std::vector<base::TrafficLightPtrs>* lights_outside_image_array,
      const TLPreprocessorOption& option, std::string* selected_camera_name);

  // @brief Project lights from HDMap onto long focus or short focus image plane
  bool ProjectLights(const CarPose& pose, const std::string& camera_name,
                     std::vector<base::TrafficLightPtr>* lights,
                     base::TrafficLightPtrs* lights_on_image,
                     base::TrafficLightPtrs* lights_outside_image);

  bool ProjectLightsAndSelectCamera(const CarPose& pose,
                                    const TLPreprocessorOption& option,
                                    std::string* selected_camera_name,
                                    std::vector<base::TrafficLightPtr>* lights);

  std::string GetMinFocalLenWorkingCameraName() const;
  std::string GetMaxFocalLenWorkingCameraName() const;

 private:
  MultiCamerasProjection projection_;
  double last_pub_img_ts_ = 0.0;

  // <timestamp, camera_name>
  std::pair<double, std::string> selected_camera_name_;
  std::map<std::string, bool> camera_is_working_flags_;
  double sync_interval_seconds_ = 0.1;  // some parameters from config file
  size_t num_cameras_ = 0;
  std::vector<base::TrafficLightPtrs> lights_on_image_array_;
  std::vector<base::TrafficLightPtrs> lights_outside_image_array_;
  base::TrafficLightPtrs lights_on_image_;
  base::TrafficLightPtrs lights_outside_image_;
  bool projections_outside_all_images_ = false;
};

}  // namespace camera
}  // namespace perception
}  // namespace apollo
