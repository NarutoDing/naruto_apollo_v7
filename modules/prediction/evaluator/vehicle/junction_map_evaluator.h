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

#include <memory>
#include <string>
#include <vector>

#include "modules/prediction/common/semantic_map.h"
#include "modules/prediction/container/obstacles/obstacles_container.h"
#include "modules/prediction/evaluator/evaluator.h"
#include "torch/extension.h"
#include "torch/script.h"

namespace apollo {
namespace prediction {

class JunctionMapEvaluator : public Evaluator {
 public:
  /**
   * @brief Constructor
   */
  JunctionMapEvaluator() = delete;
  explicit JunctionMapEvaluator(SemanticMap* semantic_map);

  /**
   * @brief Destructor
   */
  virtual ~JunctionMapEvaluator() = default;

  /**
   * @brief Clear obstacle feature map
   */
  void Clear();

  /**
   * @brief Override Evaluate
   * @param Obstacle pointer
   * @param Obstacles container
   */
  bool Evaluate(Obstacle* obstacle_ptr,
                ObstaclesContainer* obstacles_container) override;

  /**
   * @brief Extract feature vector
   * @param Obstacle pointer
   *        Feature container in a vector for receiving the feature values
   */
  bool ExtractFeatureValues(Obstacle* obstacle_ptr,
                            std::vector<double>* feature_values);

  /**
   * @brief Get the name of evaluator.
   */
  std::string GetName() override { return "JUNCTION_MAP_EVALUATOR"; }

 private:
  /**
   * @brief Load model file
   */
  void LoadModel();

 private:
  // junction exit mask
  static const size_t JUNCTION_FEATURE_SIZE = 12;
  torch::jit::script::Module torch_model_;
  torch::Device device_;
  SemanticMap* semantic_map_;
};

}  // namespace prediction
}  // namespace apollo
