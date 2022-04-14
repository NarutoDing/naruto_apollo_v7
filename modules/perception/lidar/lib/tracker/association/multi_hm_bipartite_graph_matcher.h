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
#pragma once

#include <string>
#include <vector>

#include "modules/perception/common/graph/gated_hungarian_bigraph_matcher.h"
#include "modules/perception/common/graph/secure_matrix.h"
#include "modules/perception/lidar/lib/interface/base_bipartite_graph_matcher.h"

namespace apollo {
namespace perception {
namespace lidar {

class MultiHmBipartiteGraphMatcher : public BaseBipartiteGraphMatcher {
 public:
  MultiHmBipartiteGraphMatcher();
  ~MultiHmBipartiteGraphMatcher();

  // @brief: match interface
  // @params [in]: match params
  // @params [out]: matched pair of objects & tracks
  // @params [out]: unmatched rows
  // @params [out]: unmatched cols
  void Match(const BipartiteGraphMatcherOptions &options,
             std::vector<NodeNodePair> *assignments,
             std::vector<size_t> *unassigned_rows,
             std::vector<size_t> *unassigned_cols);
  std::string Name() const { return "MultiHmBipartiteGraphMatcher"; }

 protected:
  common::GatedHungarianMatcher<float> optimizer_;
};  // class MultiHmObjectMatcher

}  // namespace lidar
}  // namespace perception
}  // namespace apollo
