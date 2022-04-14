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

#include <vector>

#include <cublas_v2.h>

#include "modules/common/math/line_segment2d.h"
#include "modules/common/math/vec2d.h"

namespace apollo {
namespace pnc_map {

struct CudaLineSegment2d {
  double x1;
  double y1;
  double x2;
  double y2;
};

class CudaNearestSegment {
 public:
  CudaNearestSegment();

  bool UpdateLineSegment(
      const std::vector<apollo::common::math::LineSegment2d>& segments);

  int FindNearestSegment(double x, double y);

  ~CudaNearestSegment();

 private:
  std::size_t size_ = 0;
  CudaLineSegment2d* host_seg_;
  double* dev_dist_;
  CudaLineSegment2d* dev_seg_;
  cublasHandle_t handle_;
};

}  // namespace pnc_map
}  // namespace apollo
