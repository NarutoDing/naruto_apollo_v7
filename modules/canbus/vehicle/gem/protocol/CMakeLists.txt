cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_gem_protocol)
message("${Green} [info] modules_canbus_vehicle_gem_protocol cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_gem_protocol_canbus_gem_protocol  SHARED
  accel_cmd_67.cc
  accel_rpt_68.cc
  brake_cmd_6b.cc
  brake_motor_rpt_1_70.cc
  brake_motor_rpt_2_71.cc
  brake_motor_rpt_3_72.cc
  brake_rpt_6c.cc
  date_time_rpt_83.cc
  global_cmd_69.cc
  global_rpt_6a.cc
  headlight_cmd_76.cc
  headlight_rpt_77.cc
  horn_cmd_78.cc
  horn_rpt_79.cc
  lat_lon_heading_rpt_82.cc
  parking_brake_status_rpt_80.cc
  shift_cmd_65.cc
  shift_rpt_66.cc
  steering_cmd_6d.cc
  steering_motor_rpt_1_73.cc
  steering_motor_rpt_2_74.cc
  steering_motor_rpt_3_75.cc
  steering_rpt_1_6e.cc
  turn_cmd_63.cc
  turn_rpt_64.cc
  vehicle_speed_rpt_6f.cc
  wheel_speed_rpt_7a.cc
  wiper_cmd_90.cc
  wiper_rpt_91.cc
  yaw_rate_rpt_81.cc
)
set_target_properties(modules_canbus_vehicle_gem_protocol_canbus_gem_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_gem_protocol_canbus_gem_protocol
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::gem::protocol::canbus_gem_protocol  ALIAS   modules_canbus_vehicle_gem_protocol_canbus_gem_protocol)

