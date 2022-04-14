/******************************************************************************
 * Copyright 2021 The Apollo Authors. All Rights Reserved.
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

#include "modules/planning/tasks/deciders/open_space_decider/open_space_pre_stop_decider.h"

#include <memory>
#include <string>
#include <vector>

#include "modules/common/vehicle_state/vehicle_state_provider.h"
#include "modules/map/pnc_map/path.h"
#include "modules/planning/common/planning_context.h"
#include "modules/planning/common/util/common.h"

namespace apollo {
namespace planning {
using apollo::common::PointENU;
using apollo::common::ErrorCode;
using apollo::common::Status;
using apollo::common::VehicleState;
using apollo::common::math::Vec2d;
using apollo::common::math::Polygon2d;
using apollo::hdmap::HDMapUtil;
using apollo::hdmap::JunctionInfoConstPtr;
using apollo::hdmap::ParkingSpaceInfoConstPtr;
using apollo::routing::RoutingRequest;

OpenSpacePreStopDecider::OpenSpacePreStopDecider(
    const TaskConfig& config,
    const std::shared_ptr<DependencyInjector>& injector)
    : Decider(config, injector) {
  ACHECK(config.has_open_space_pre_stop_decider_config());
}

Status OpenSpacePreStopDecider::Process(
    Frame* frame, ReferenceLineInfo* reference_line_info) {
  CHECK_NOTNULL(frame);
  CHECK_NOTNULL(reference_line_info);
  open_space_pre_stop_decider_config_ =
      config_.open_space_pre_stop_decider_config();
  double target_s = 0.0;
  const auto& stop_type = open_space_pre_stop_decider_config_.stop_type();
  switch (stop_type) {
    case OpenSpacePreStopDeciderConfig::PARKING:
      if (!CheckParkingSpotPreStop(frame, reference_line_info, &target_s)) {
        const std::string msg = "Checking parking spot pre stop fails";
        AERROR << msg;
        return Status(ErrorCode::PLANNING_ERROR, msg);
      }
      SetParkingSpotStopFence(target_s, frame, reference_line_info);
      break;
    case OpenSpacePreStopDeciderConfig::PULL_OVER:
      if (!CheckPullOverPreStop(frame, reference_line_info, &target_s)) {
        const std::string msg = "Checking pull over pre stop fails";
        AERROR << msg;
        return Status(ErrorCode::PLANNING_ERROR, msg);
      }
      SetPullOverStopFence(target_s, frame, reference_line_info);
      break;
    case OpenSpacePreStopDeciderConfig::DEAD_END_PRE_STOP:
      if (!CheckDeadEndPreStop(frame, reference_line_info, &target_s)) {
        const std::string msg = "Checking dead end pre stop fails";
        AERROR << msg;
        return Status(ErrorCode::PLANNING_ERROR, msg);
      }
      SetDeadEndStopFence(target_s, frame, reference_line_info);
      break;
    default:
      const std::string msg = "This stop type not implemented";
      AERROR << msg;
      return Status(ErrorCode::PLANNING_ERROR, msg);
  }
  return Status::OK();
}

bool OpenSpacePreStopDecider::CheckPullOverPreStop(
    Frame* const frame, ReferenceLineInfo* const reference_line_info,
    double* target_s) {
  *target_s = 0.0;
  const auto& pull_over_status =
      injector_->planning_context()->planning_status().pull_over();
  if (pull_over_status.has_position() && pull_over_status.position().has_x() &&
      pull_over_status.position().has_y()) {
    common::SLPoint pull_over_sl;
    const auto& reference_line = reference_line_info->reference_line();
    reference_line.XYToSL(pull_over_status.position(), &pull_over_sl);
    *target_s = pull_over_sl.s();
  }
  return true;
}

bool OpenSpacePreStopDecider::CheckParkingSpotPreStop(
    Frame* const frame, ReferenceLineInfo* const reference_line_info,
    double* target_s) {
  const auto &routing_request =
      frame->local_view().routing->routing_request();
  auto corner_point =
      routing_request.parking_info().corner_point();
  const auto& target_parking_spot_id =
      frame->open_space_info().target_parking_spot_id();
  const auto& nearby_path = reference_line_info->reference_line().map_path();
  if (target_parking_spot_id.empty()) {
    AERROR << "no target parking spot id found when setting pre stop fence";
    return false;
  }

  double target_area_center_s = 0.0;
  bool target_area_found = false;
  const auto& parking_space_overlaps = nearby_path.parking_space_overlaps();
  ParkingSpaceInfoConstPtr target_parking_spot_ptr;
  const hdmap::HDMap* hdmap = hdmap::HDMapUtil::BaseMapPtr();
  for (const auto& parking_overlap : parking_space_overlaps) {
    if (parking_overlap.object_id == target_parking_spot_id) {
      // TODO(Jinyun) parking overlap s are wrong on map, not usable
      // target_area_center_s =
      //     (parking_overlap.start_s + parking_overlap.end_s) / 2.0;
      hdmap::Id id;
      id.set_id(parking_overlap.object_id);
      target_parking_spot_ptr = hdmap->GetParkingSpaceById(id);
      Vec2d left_bottom_point =
          target_parking_spot_ptr->polygon().points().at(0);
      Vec2d right_bottom_point =
          target_parking_spot_ptr->polygon().points().at(1);
      left_bottom_point.set_x(corner_point.point().at(0).x());
      left_bottom_point.set_y(corner_point.point().at(0).y());
      right_bottom_point.set_x(corner_point.point().at(1).x());
      right_bottom_point.set_y(corner_point.point().at(1).y());
      double left_bottom_point_s = 0.0;
      double left_bottom_point_l = 0.0;
      double right_bottom_point_s = 0.0;
      double right_bottom_point_l = 0.0;
      nearby_path.GetNearestPoint(left_bottom_point, &left_bottom_point_s,
                                  &left_bottom_point_l);
      nearby_path.GetNearestPoint(right_bottom_point, &right_bottom_point_s,
                                  &right_bottom_point_l);
      target_area_center_s = (left_bottom_point_s + right_bottom_point_s) / 2.0;
      target_area_found = true;
    }
  }

  if (!target_area_found) {
    AERROR << "no target parking spot found on reference line";
    return false;
  }
  *target_s = target_area_center_s;
  return true;
}

bool OpenSpacePreStopDecider::SelectTargetDeadEndJunction(
    std::vector<JunctionInfoConstPtr>* junctions,
    const apollo::common::PointENU& dead_end_point,
    JunctionInfoConstPtr* target_junction) {
  // warning: the car only be the one junction
  size_t junction_num = junctions->size();
  if (junction_num <= 0) {
    ADEBUG << "No junctions frim map";
    return false;
  }
  Vec2d target_point = {dead_end_point.x(), dead_end_point.y()};
  for (size_t i = 0; i < junction_num; ++i) {
    if (junctions->at(i)->junction().type() == 5) {
      Polygon2d polygon = junctions->at(i)->polygon();
      if (polygon.IsPointIn(target_point)) {
        *target_junction = junctions->at(i);
        ADEBUG << "car in the junction";
        return true;
      } else {
        return false;
      }
    } else {
      ADEBUG << "No dead end junction";
      return false;
    }
  }
  return true;
}

bool OpenSpacePreStopDecider::CheckDeadEndPreStop(
  Frame* const frame,
  ReferenceLineInfo* const reference_line_info,
  double* target_s) {
  const auto& routing_type = frame->local_view().
    routing->routing_request().dead_end_info().dead_end_routing_type();
  size_t waypoint_num =
    frame->local_view().routing->routing_request().waypoint().size();
  if (routing_type == routing::ROUTING_IN) {
    dead_end_point_ = frame->local_view().routing->routing_request().
                    waypoint().at(waypoint_num - 1).pose();
  } else if (routing_type == routing::ROUTING_OUT) {
    dead_end_point_ = frame->local_view().routing->routing_request().
                    waypoint().at(0).pose();
  }
  const hdmap::HDMap* base_map_ptr = HDMapUtil::BaseMapPtr();
  std::vector<JunctionInfoConstPtr> junctions;
  JunctionInfoConstPtr junction;
  if (base_map_ptr->GetJunctions(dead_end_point_, 1.0, &junctions) != 0) {
    ADEBUG << "Fail to get junctions from sim_map.";
    return false;
  }
  if (junctions.size() <= 0) {
    ADEBUG << "No junctions from map";
    return false;
  }
  if (!SelectTargetDeadEndJunction(&junctions, dead_end_point_, &junction)) {
    ADEBUG << "Target Dead End not found";
    return false;
  }
  // compute the x value of dead end
  auto points = junction->polygon().points();
  const auto& nearby_path =
      reference_line_info->reference_line().map_path();
  Vec2d first_point = points.front();
  // the last point's s value may be unsuitable
  Vec2d last_point = points.back();
  double first_point_s = 0.0;
  double first_point_l = 0.0;
  double last_point_s = 0.0;
  double last_point_l = 0.0;
  nearby_path.GetNearestPoint(first_point, &first_point_s,
                              &first_point_l);
  nearby_path.GetNearestPoint(last_point, &last_point_s,
                              &last_point_l);
  double center_s = (first_point_s + last_point_s) / 2.0;
  *target_s = center_s;
  return true;
}

void OpenSpacePreStopDecider::SetDeadEndStopFence(
    const double target_s, Frame* const frame,
    ReferenceLineInfo* const reference_line_info) {
  double stop_line_s = 0.0;
  double stop_distance_to_target =
      open_space_pre_stop_decider_config_.stop_distance_to_target();
  CHECK_GE(stop_distance_to_target, 1.0e-8);
  // get the stop point s
  stop_line_s = target_s - stop_distance_to_target;
  // set stop fence
  const std::string stop_wall_id = OPEN_SPACE_STOP_ID;
  std::vector<std::string> wait_for_obstacles;
  frame->mutable_open_space_info()->set_open_space_pre_stop_fence_s(
      stop_line_s);
  util::BuildStopDecision(stop_wall_id, stop_line_s, 0.0,
                          StopReasonCode::STOP_REASON_PRE_OPEN_SPACE_STOP,
                          wait_for_obstacles, "OpenSpacePreStopDecider", frame,
                          reference_line_info);
}

void OpenSpacePreStopDecider::SetParkingSpotStopFence(
    const double target_s, Frame* const frame,
    ReferenceLineInfo* const reference_line_info) {
  const auto& nearby_path = reference_line_info->reference_line().map_path();
  const double adc_front_edge_s = reference_line_info->AdcSlBoundary().end_s();
  const VehicleState& vehicle_state = frame->vehicle_state();
  double stop_line_s = 0.0;
  double stop_distance_to_target =
      open_space_pre_stop_decider_config_.stop_distance_to_target();
  double static_linear_velocity_epsilon = 1.0e-2;
  CHECK_GE(stop_distance_to_target, 1.0e-8);
  double target_vehicle_offset = target_s - adc_front_edge_s;
  if (target_vehicle_offset > stop_distance_to_target) {
    stop_line_s = target_s - stop_distance_to_target;
  } else if (std::abs(target_vehicle_offset) < stop_distance_to_target) {
    stop_line_s = target_s + stop_distance_to_target;
  } else if (target_vehicle_offset < -stop_distance_to_target) {
    if (!frame->open_space_info().pre_stop_rightaway_flag()) {
      // TODO(Jinyun) Use constant comfortable deacceleration rather than
      // distance by config to set stop fence
      stop_line_s =
          adc_front_edge_s +
          open_space_pre_stop_decider_config_.rightaway_stop_distance();
      if (std::abs(vehicle_state.linear_velocity()) <
          static_linear_velocity_epsilon) {
        stop_line_s = adc_front_edge_s;
      }
      *(frame->mutable_open_space_info()->mutable_pre_stop_rightaway_point()) =
          nearby_path.GetSmoothPoint(stop_line_s);
      frame->mutable_open_space_info()->set_pre_stop_rightaway_flag(true);
    } else {
      double stop_point_s = 0.0;
      double stop_point_l = 0.0;
      nearby_path.GetNearestPoint(
          frame->open_space_info().pre_stop_rightaway_point(), &stop_point_s,
          &stop_point_l);
      stop_line_s = stop_point_s;
    }
  }

  const std::string stop_wall_id = OPEN_SPACE_STOP_ID;
  std::vector<std::string> wait_for_obstacles;
  frame->mutable_open_space_info()->set_open_space_pre_stop_fence_s(
      stop_line_s);
  util::BuildStopDecision(stop_wall_id, stop_line_s, 0.0,
                          StopReasonCode::STOP_REASON_PRE_OPEN_SPACE_STOP,
                          wait_for_obstacles, "OpenSpacePreStopDecider", frame,
                          reference_line_info);
}

void OpenSpacePreStopDecider::SetPullOverStopFence(
    const double target_s, Frame* const frame,
    ReferenceLineInfo* const reference_line_info) {
  const auto& nearby_path = reference_line_info->reference_line().map_path();
  const double adc_front_edge_s = reference_line_info->AdcSlBoundary().end_s();
  const VehicleState& vehicle_state = frame->vehicle_state();
  double stop_line_s = 0.0;
  double stop_distance_to_target =
      open_space_pre_stop_decider_config_.stop_distance_to_target();
  double static_linear_velocity_epsilon = 1.0e-2;
  CHECK_GE(stop_distance_to_target, 1.0e-8);
  double target_vehicle_offset = target_s - adc_front_edge_s;
  if (target_vehicle_offset > stop_distance_to_target) {
    stop_line_s = target_s - stop_distance_to_target;
  } else {
    if (!frame->open_space_info().pre_stop_rightaway_flag()) {
      // TODO(Jinyun) Use constant comfortable deacceleration rather than
      // distance by config to set stop fence
      stop_line_s =
          adc_front_edge_s +
          open_space_pre_stop_decider_config_.rightaway_stop_distance();
      if (std::abs(vehicle_state.linear_velocity()) <
          static_linear_velocity_epsilon) {
        stop_line_s = adc_front_edge_s;
      }
      *(frame->mutable_open_space_info()->mutable_pre_stop_rightaway_point()) =
          nearby_path.GetSmoothPoint(stop_line_s);
      frame->mutable_open_space_info()->set_pre_stop_rightaway_flag(true);
    } else {
      double stop_point_s = 0.0;
      double stop_point_l = 0.0;
      nearby_path.GetNearestPoint(
          frame->open_space_info().pre_stop_rightaway_point(), &stop_point_s,
          &stop_point_l);
      stop_line_s = stop_point_s;
    }
  }

  const std::string stop_wall_id = OPEN_SPACE_STOP_ID;
  std::vector<std::string> wait_for_obstacles;
  frame->mutable_open_space_info()->set_open_space_pre_stop_fence_s(
      stop_line_s);
  util::BuildStopDecision(stop_wall_id, stop_line_s, 0.0,
                          StopReasonCode::STOP_REASON_PRE_OPEN_SPACE_STOP,
                          wait_for_obstacles, "OpenSpacePreStopDecider", frame,
                          reference_line_info);
}
}  // namespace planning
}  // namespace apollo
