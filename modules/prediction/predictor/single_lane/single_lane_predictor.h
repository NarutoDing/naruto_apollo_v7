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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *implied. See the License for the specific language governing
 *permissions and limitations under the License.
 *****************************************************************************/
/**
 * @file
 */

#pragma once

#include <vector>

#include "modules/prediction/predictor/sequence/sequence_predictor.h"

namespace apollo {
namespace prediction {

class SingleLanePredictor : public SequencePredictor {
 public:
  /**
   * @brief Constructor
   */
  SingleLanePredictor();

  /**
   * @brief Destructor
   */
  virtual ~SingleLanePredictor() = default;

  /**
   * @brief Make prediction
   * @param ADC trajectory container
   * @param Obstacle pointer
   * @param Obstacles container
   * @return If predicted successfully
   */
  bool Predict(const ADCTrajectoryContainer* adc_trajectory_container,
               Obstacle* obstacle,
               ObstaclesContainer* obstacles_container) override;

 protected:
  /**
   * @brief Draw lane sequence trajectory points
   * @param Obstacle
   * @param Lane sequence
   * @param Total prediction time
   * @param Prediction period
   * @param A vector of generated trajectory points
   */
  void GenerateTrajectoryPoints(
      const Obstacle& obstacle, const LaneSequence& lane_sequence,
      const double total_time, const double period,
      std::vector<apollo::common::TrajectoryPoint>* points);
};

}  // namespace prediction
}  // namespace apollo
