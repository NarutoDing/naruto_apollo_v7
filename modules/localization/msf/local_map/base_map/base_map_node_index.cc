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

#include "modules/localization/msf/local_map/base_map/base_map_node_index.h"

#include "cyber/common/log.h"

namespace apollo {
namespace localization {
namespace msf {

MapNodeIndex::MapNodeIndex() {}

bool MapNodeIndex::operator<(const MapNodeIndex& index) const {
  // Compare elements by priority.
  return std::forward_as_tuple(resolution_id_, zone_id_, m_, n_) <
         std::forward_as_tuple(index.resolution_id_, index.zone_id_, index.m_,
                               index.n_);
}

bool MapNodeIndex::operator==(const MapNodeIndex& index) const {
  return resolution_id_ == index.resolution_id_ && zone_id_ == index.zone_id_ &&
         m_ == index.m_ && n_ == index.n_;
}

bool MapNodeIndex::operator!=(const MapNodeIndex& index) const {
  return !(*this == index);
}

std::string MapNodeIndex::ToString() const {
  std::ostringstream ss;
  ss << "Map node (Resolution ID: " << resolution_id_
     << " Zone ID: " << zone_id_ << " Easting: " << n_ << " Northing: " << m_
     << ")";
  return ss.str();
}

MapNodeIndex MapNodeIndex::GetMapNodeIndex(const BaseMapConfig& option,
                                           const Eigen::Vector3d& coordinate,
                                           unsigned int resolution_id,
                                           int zone_id) {
  Eigen::Vector2d coord2d(coordinate[0], coordinate[1]);
  return GetMapNodeIndex(option, coord2d, resolution_id, zone_id);
}

MapNodeIndex MapNodeIndex::GetMapNodeIndex(const BaseMapConfig& option,
                                           const Eigen::Vector2d& coordinate,
                                           unsigned int resolution_id,
                                           int zone_id) {
  DCHECK_LT(resolution_id, option.map_resolutions_.size());
  MapNodeIndex index;
  index.resolution_id_ = resolution_id;
  index.zone_id_ = zone_id;
  int n = static_cast<int>((coordinate[0] - option.map_range_.GetMinX()) /
                           (static_cast<float>(option.map_node_size_x_) *
                            option.map_resolutions_[resolution_id]));
  int m = static_cast<int>((coordinate[1] - option.map_range_.GetMinY()) /
                           (static_cast<float>(option.map_node_size_y_) *
                            option.map_resolutions_[resolution_id]));
  if (n >= 0 && m >= 0 &&
      n < static_cast<int>(GetMapIndexRangeEast(option, resolution_id)) &&
      m < static_cast<int>(GetMapIndexRangeNorth(option, resolution_id))) {
    index.m_ = m;
    index.n_ = n;
  } else {
    DCHECK(false);  // should never reach here
  }
  return index;
}

unsigned int MapNodeIndex::GetMapIndexRangeEast(const BaseMapConfig& option,
                                                unsigned int resolution_id) {
  return static_cast<unsigned int>(
      (option.map_range_.GetMaxX() - option.map_range_.GetMinX()) /
      (static_cast<float>(option.map_node_size_x_) *
       option.map_resolutions_[resolution_id]));
}

unsigned int MapNodeIndex::GetMapIndexRangeNorth(const BaseMapConfig& option,
                                                 unsigned int resolution_id) {
  return static_cast<unsigned int>(
      (option.map_range_.GetMaxY() - option.map_range_.GetMinY()) /
      (static_cast<float>(option.map_node_size_y_) *
       option.map_resolutions_[resolution_id]));
}

std::ostream& operator<<(std::ostream& cerr, const MapNodeIndex& index) {
  cerr << index.ToString();
  return cerr;
}

}  // namespace msf
}  // namespace localization
}  // namespace apollo
