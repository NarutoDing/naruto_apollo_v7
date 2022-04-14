cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_lincoln_protocol)
message("${Green} [info] modules_canbus_vehicle_lincoln_protocol cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_lincoln_protocol_canbus_lincoln_protocol  SHARED
  accel_6b.cc
  brake_60.cc
  brake_61.cc
  brakeinfo_74.cc
  fuellevel_72.cc
  gear_66.cc
  gear_67.cc
  gps_6d.cc
  gps_6e.cc
  gps_6f.cc
  gyro_6c.cc
  license_7e.cc
  misc_69.cc
  steering_64.cc
  steering_65.cc
  surround_73.cc
  throttle_62.cc
  throttle_63.cc
  throttleinfo_75.cc
  tirepressure_71.cc
  turnsignal_68.cc
  version_7f.cc
  wheelspeed_6a.cc
)
set_target_properties(modules_canbus_vehicle_lincoln_protocol_canbus_lincoln_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_lincoln_protocol_canbus_lincoln_protocol
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::lincoln::protocol::canbus_lincoln_protocol  ALIAS   modules_canbus_vehicle_lincoln_protocol_canbus_lincoln_protocol)

