cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_lexus)
message("${Green} [info] modules_canbus_vehicle_lexus cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_lexus_lexus_vehicle_factory  SHARED
  lexus_vehicle_factory.cc
)
set_target_properties(modules_canbus_vehicle_lexus_lexus_vehicle_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_lexus_lexus_vehicle_factory
  modules::canbus::vehicle::lexus::lexus_controller
  modules::canbus::vehicle::lexus::lexus_message_manager
  modules::canbus::proto::canbus_conf_cc_proto
  modules::canbus::proto::vehicle_parameter_cc_proto
  modules::canbus::vehicle::abstract_vehicle_factory
)
add_library(modules::canbus::vehicle::lexus::lexus_vehicle_factory  ALIAS   modules_canbus_vehicle_lexus_lexus_vehicle_factory)

add_library(modules_canbus_vehicle_lexus_lexus_message_manager  SHARED
  lexus_message_manager.cc
)
set_target_properties(modules_canbus_vehicle_lexus_lexus_message_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_lexus_lexus_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::lexus::protocol::canbus_lexus_protocol
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::lexus::lexus_message_manager  ALIAS   modules_canbus_vehicle_lexus_lexus_message_manager)

add_library(modules_canbus_vehicle_lexus_lexus_controller  SHARED
  lexus_controller.cc
)
set_target_properties(modules_canbus_vehicle_lexus_lexus_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_lexus_lexus_controller
  modules::canbus::vehicle::lexus::lexus_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::vehicle_controller_base
  modules::canbus::vehicle::lexus::protocol::canbus_lexus_protocol
  modules::drivers::canbus::can_comm::can_sender
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::lexus::lexus_controller  ALIAS   modules_canbus_vehicle_lexus_lexus_controller)

