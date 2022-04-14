cmake_minimum_required(VERSION 3.16)

project(modules_drivers_radar_racobit_radar_protocol)
message("${Green} [info] modules_drivers_radar_racobit_radar_protocol cmakelist ${ColourReset}")

file(GLOB all_srcs ./*.cc)
add_library(modules_drivers_radar_racobit_radar_protocol_drivers_racobit_radar_protocol  SHARED
  ${all_srcs}
)
set_target_properties(modules_drivers_radar_racobit_radar_protocol_drivers_racobit_radar_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_radar_racobit_radar_protocol_drivers_racobit_radar_protocol
  modules::common::proto::header_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::proto::can_card_parameter_cc_proto
  modules::drivers::proto::racobit_radar_cc_proto
  modules::drivers::radar::racobit_radar::proto::racobit_radar_conf_cc_proto
  
)
add_library(modules::drivers::radar::racobit_radar::protocol::drivers_racobit_radar_protocol  ALIAS   modules_drivers_radar_racobit_radar_protocol_drivers_racobit_radar_protocol)

