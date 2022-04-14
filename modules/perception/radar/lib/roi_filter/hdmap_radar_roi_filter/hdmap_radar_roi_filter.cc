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
#include <vector>

#include "modules/perception/radar/lib/roi_filter/hdmap_radar_roi_filter/hdmap_radar_roi_filter.h"

namespace apollo {
namespace perception {
namespace radar {

bool HdmapRadarRoiFilter::RoiFilter(const RoiFilterOptions& options,
                                    base::FramePtr radar_frame) {
  std::vector<base::ObjectPtr> origin_objects = radar_frame->objects;
  return common::ObjectInRoiCheck(options.roi, origin_objects,
                                  &radar_frame->objects);
}

std::string HdmapRadarRoiFilter::Name() const { return "HdmapRadarRoiFilter"; }

PERCEPTION_REGISTER_ROI_FILTER(HdmapRadarRoiFilter);

}  // namespace radar
}  // namespace perception
}  // namespace apollo
