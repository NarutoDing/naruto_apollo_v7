cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_ge3_protocol)
message("${Green} [info] modules_canbus_vehicle_ge3_protocol cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_ge3_protocol_canbus_ge3_protocol_pc_bcm_201  SHARED
  pc_bcm_201.cc
  pc_bcs_202.cc
  pc_epb_203.cc
  pc_eps_204.cc
  pc_vcu_205.cc
  scu_1_301.cc
  scu_2_302.cc
  scu_3_303.cc
  scu_bcm_304.cc
  scu_bcs_1_306.cc
  scu_bcs_2_307.cc
  scu_bcs_3_308.cc
  scu_epb_310.cc
  scu_eps_311.cc
  scu_vcu_1_312.cc
  scu_vcu_2_313.cc
)
set_target_properties(modules_canbus_vehicle_ge3_protocol_canbus_ge3_protocol_pc_bcm_201  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ge3_protocol_canbus_ge3_protocol_pc_bcm_201
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ge3::protocol::canbus_ge3_protocol_pc_bcm_201  ALIAS   modules_canbus_vehicle_ge3_protocol_canbus_ge3_protocol_pc_bcm_201)

