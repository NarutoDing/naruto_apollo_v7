cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_wey_protocol)
message("${Green} [info] modules_canbus_vehicle_wey_protocol cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_wey_protocol_canbus_wey_protocol  SHARED
  ads1_111.cc
  ads3_38e.cc
  ads_eps_113.cc
  ads_req_vin_390.cc
  ads_shifter_115.cc
  fail_241.cc
  fbs1_243.cc
  fbs2_240.cc
  fbs3_237.cc
  fbs4_235.cc
  status_310.cc
  vin_resp1_391.cc
  vin_resp2_392.cc
  vin_resp3_393.cc
)
set_target_properties(modules_canbus_vehicle_wey_protocol_canbus_wey_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_wey_protocol_canbus_wey_protocol
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::wey::protocol::canbus_wey_protocol  ALIAS   modules_canbus_vehicle_wey_protocol_canbus_wey_protocol)

