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

/**
 * @file
 **/

#include "modules/planning/scenarios/park/valet_parking/stage_approaching_parking_spot.h"

#include "modules/common/configs/vehicle_config_helper.h"
#include "modules/common/vehicle_state/vehicle_state_provider.h"

namespace apollo {
namespace planning {
namespace scenario {
namespace valet_parking {

Stage::StageStatus StageApproachingParkingSpot::Process(
    const common::TrajectoryPoint& planning_init_point, Frame* frame) {
  ADEBUG << "stage: StageApproachingParkingSpot";
  CHECK_NOTNULL(frame);
  GetContext()->target_parking_spot_id.clear();
  if (frame->local_view().routing->routing_request().has_parking_info() &&
      frame->local_view()
          .routing->routing_request()
          .parking_info()
          .has_parking_space_id()) {
    GetContext()->target_parking_spot_id = frame->local_view()
                                               .routing->routing_request()
                                               .parking_info()
                                               .parking_space_id();
  } else {
    AERROR << "No parking space id from routing";
    return StageStatus::ERROR;
  }

  if (GetContext()->target_parking_spot_id.empty()) {
    return StageStatus::ERROR;
  }

  *(frame->mutable_open_space_info()->mutable_target_parking_spot_id()) =
      GetContext()->target_parking_spot_id;
  frame->mutable_open_space_info()->set_pre_stop_rightaway_flag(
      GetContext()->pre_stop_rightaway_flag);
  *(frame->mutable_open_space_info()->mutable_pre_stop_rightaway_point()) =
      GetContext()->pre_stop_rightaway_point;

  bool plan_ok = ExecuteTaskOnReferenceLine(planning_init_point, frame);
  if (!plan_ok) {
    AERROR << "StopSignUnprotectedStagePreStop planning error";
    return StageStatus::ERROR;
  }

  GetContext()->pre_stop_rightaway_flag =
      frame->open_space_info().pre_stop_rightaway_flag();
  GetContext()->pre_stop_rightaway_point =
      frame->open_space_info().pre_stop_rightaway_point();

  if (CheckADCStop(*frame)) {
    next_stage_ = ScenarioConfig::VALET_PARKING_PARKING;
    return Stage::FINISHED;
  }

  return Stage::RUNNING;
}

bool StageApproachingParkingSpot::CheckADCStop(const Frame& frame) {
  const auto& reference_line_info = frame.reference_line_info().front();
  const double adc_speed = injector_->vehicle_state()->linear_velocity();
  const double max_adc_stop_speed = common::VehicleConfigHelper::Instance()
                                        ->GetConfig()
                                        .vehicle_param()
                                        .max_abs_speed_when_stopped();
  if (adc_speed > max_adc_stop_speed) {
    ADEBUG << "ADC not stopped: speed[" << adc_speed << "]";
    return false;
  }

  // check stop close enough to stop line of the stop_sign
  const double adc_front_edge_s = reference_line_info.AdcSlBoundary().end_s();
  const double stop_fence_start_s =
      frame.open_space_info().open_space_pre_stop_fence_s();
  const double distance_stop_line_to_adc_front_edge =
      stop_fence_start_s - adc_front_edge_s;

  if (distance_stop_line_to_adc_front_edge >
      scenario_config_.max_valid_stop_distance()) {
    ADEBUG << "not a valid stop. too far from stop line.";
    return false;
  }
  return true;
}

}  // namespace valet_parking
}  // namespace scenario
}  // namespace planning
}  // namespace apollo
