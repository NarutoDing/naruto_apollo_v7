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

#include <string>

#include "cyber/common/macros.h"
#include "modules/perception/radar/lib/interface/base_roi_filter.h"

namespace apollo {
namespace perception {
namespace radar {

class HdmapRadarRoiFilter : public BaseRoiFilter {
 public:
  HdmapRadarRoiFilter() : BaseRoiFilter() {}
  virtual ~HdmapRadarRoiFilter() {}

  bool Init() override { return true; }

  bool RoiFilter(const RoiFilterOptions& options,
                 base::FramePtr radar_frame) override;

  std::string Name() const override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HdmapRadarRoiFilter);
};

}  // namespace radar
}  // namespace perception
}  // namespace apollo
