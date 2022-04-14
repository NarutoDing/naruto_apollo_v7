cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_lexus_protocol)
message("${Green} [info] modules_canbus_vehicle_lexus_protocol cmakelist ${ColourReset}")

file(GLOB all_srcs ./*.cc)
add_library(modules_canbus_vehicle_lexus_protocol_canbus_lexus_protocol  SHARED
  ${all_srcs}
)
set_target_properties(modules_canbus_vehicle_lexus_protocol_canbus_lexus_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_lexus_protocol_canbus_lexus_protocol
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::lexus::protocol::canbus_lexus_protocol  ALIAS   modules_canbus_vehicle_lexus_protocol_canbus_lexus_protocol)

