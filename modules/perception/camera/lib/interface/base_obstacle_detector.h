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

#include <memory>
#include <string>

#include "modules/perception/base/camera.h"
#include "modules/perception/camera/common/camera_frame.h"
#include "modules/perception/camera/lib/interface/base_init_options.h"
#include "modules/perception/lib/registerer/registerer.h"

namespace apollo {
namespace perception {
namespace camera {

struct ObstacleDetectorInitOptions : public BaseInitOptions {
  std::shared_ptr<base::BaseCameraModel> base_camera_model = nullptr;
  Eigen::Matrix3f intrinsics;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;

struct ObstacleDetectorOptions {};

class BaseObstacleDetector {
 public:
  BaseObstacleDetector() = default;

  virtual ~BaseObstacleDetector() = default;

  virtual bool Init(const ObstacleDetectorInitOptions &options =
                        ObstacleDetectorInitOptions()) = 0;

  // @brief: detect obstacle from image.
  // @param [in]: options
  // @param [in/out]: frame
  // obstacle type and 2D bbox should be filled, required,
  // 3D information of obstacle can be filled, optional.
  virtual bool Detect(const ObstacleDetectorOptions &options,
                      CameraFrame *frame) = 0;

  virtual std::string Name() const = 0;

  BaseObstacleDetector(const BaseObstacleDetector &) = delete;
  BaseObstacleDetector &operator=(const BaseObstacleDetector &) = delete;
};  // class BaseObstacleDetector

PERCEPTION_REGISTER_REGISTERER(BaseObstacleDetector);
#define REGISTER_OBSTACLE_DETECTOR(name) \
  PERCEPTION_REGISTER_CLASS(BaseObstacleDetector, name)

}  // namespace camera
}  // namespace perception
}  // namespace apollo
