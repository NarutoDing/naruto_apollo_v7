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

/*
Copyright (C) 2006 Pedro Felzenszwalb
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/
#pragma once
#include <algorithm>
#include <cmath>
#include <vector>
#include "modules/perception/lidar/detector/ncut_segmentation/common/graph_felzenszwalb/image.h"

namespace apollo {
namespace perception {
namespace lidar {
// convolve src with mask.  dst is flipped!
void convolve_even(Image<float> *src, Image<float> *dst,
                   const std::vector<float> &mask) {
  int width = src->width();
  int height = src->height();
  int len = mask.size();
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float sum = mask[0] * imRef(src, x, y);
      for (int i = 1; i < len; i++) {
        sum += mask[i] * (imRef(src, std::max(x - i, 0), y) +
                          imRef(src, std::min(x + i, width - 1), y));
      }
      imRef(dst, y, x) = sum;
    }
  }
}
// convolve src with mask.  dst is flipped!
void convolve_odd(Image<float> *src, Image<float> *dst,
                  const std::vector<float> &mask) {
  int width = src->width();
  int height = src->height();
  int len = mask.size();
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float sum = mask[0] * imRef(src, x, y);
      for (int i = 1; i < len; i++) {
        sum += mask[i] * (imRef(src, std::max(x - i, 0), y) -
                          imRef(src, std::min(x + i, width - 1), y));
      }
      imRef(dst, y, x) = sum;
    }
  }
}
}  // namespace lidar
}  // namespace perception
}  // namespace apollo
