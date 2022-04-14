/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
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
#pragma once

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "modules/perception/base/point_cloud.h"

namespace apollo {
namespace perception {
namespace lidar {

class FloodFill {
 public:
  FloodFill() = default;
  FloodFill(float grid_radius, float cell_size)
      : _grid_radius(grid_radius), _cell_size(cell_size) {}
  void GetSegments(base::PointFCloudConstPtr cloud,
                   std::vector<std::vector<int>>* segments_indices,
                   std::vector<int>* num_cells_per_segment);
  // The grids at the boundary are valid.
  int Pos(float x, float y) const;
  bool Pos2d(float x, float y, int* irow, int* jcol) const;
  void BuildGrid(base::PointFCloudConstPtr cloud);
  void SetGridRadius(float grid_radius) { _grid_radius = grid_radius; }
  void SetCellSize(float cell_size) { _cell_size = cell_size; }
  int GetNumRows() const { return _grid_num_rows; }
  int GetNumCols() const { return _grid_num_cols; }
  int GetNumCells() const { return _grid_size; }
  const std::vector<int>& GetPointIdxInGrid() const {
    return _point_cloud_grid_idx;
  }

 private:
  bool IsValidRowIndex(int i) const { return (i >= 0 && i < _grid_num_rows); }
  bool IsValidColIndex(int j) const { return (j >= 0 && j < _grid_num_cols); }
  int GetConnectedComponents();
  void DfsColoring(int i, int j, int curr_component);
  float _grid_radius = 0.0;
  float _cell_size = 0.0;
  float _offset_x = 0.0;
  float _offset_y = 0.0;
  int _grid_num_rows = 0;
  int _grid_num_cols = 0;
  int _grid_size = 0;
  int _num_points = 0;
  std::vector<int> _point_cloud_grid_idx;
  std::vector<int> _label;
};
}  // namespace lidar
}  // namespace perception
}  // namespace apollo
