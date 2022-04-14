cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_ge3)
message("${Green} [info] modules_canbus_vehicle_ge3 cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_ge3_ge3_vehicle_factory  SHARED
  ge3_vehicle_factory.cc
)
set_target_properties(modules_canbus_vehicle_ge3_ge3_vehicle_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ge3_ge3_vehicle_factory
  modules::canbus::vehicle::ge3::ge3_controller
  modules::canbus::vehicle::ge3::ge3_message_manager
  modules::canbus::proto::vehicle_parameter_cc_proto
  modules::canbus::vehicle::abstract_vehicle_factory
)
add_library(modules::canbus::vehicle::ge3::ge3_vehicle_factory  ALIAS   modules_canbus_vehicle_ge3_ge3_vehicle_factory)

add_library(modules_canbus_vehicle_ge3_ge3_message_manager  SHARED
  ge3_message_manager.cc
)
set_target_properties(modules_canbus_vehicle_ge3_ge3_message_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ge3_ge3_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::ge3::protocol::canbus_ge3_protocol_pc_bcm_201
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ge3::ge3_message_manager  ALIAS   modules_canbus_vehicle_ge3_ge3_message_manager)

add_library(modules_canbus_vehicle_ge3_ge3_controller  SHARED
  ge3_controller.cc
)
set_target_properties(modules_canbus_vehicle_ge3_ge3_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ge3_ge3_controller
  modules::canbus::vehicle::ge3::ge3_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::vehicle_controller_base
  modules::canbus::vehicle::ge3::protocol::canbus_ge3_protocol_pc_bcm_201
  modules::drivers::canbus::can_comm::can_sender
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ge3::ge3_controller  ALIAS   modules_canbus_vehicle_ge3_ge3_controller)

