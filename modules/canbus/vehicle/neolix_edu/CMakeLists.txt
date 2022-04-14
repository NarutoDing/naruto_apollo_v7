cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_neolix_edu)
message("${Green} [info] modules_canbus_vehicle_neolix_edu cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_neolix_edu_neolix_edu_vehicle_factory  SHARED
  neolix_edu_vehicle_factory.cc
)
set_target_properties(modules_canbus_vehicle_neolix_edu_neolix_edu_vehicle_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_neolix_edu_neolix_edu_vehicle_factory
  modules::canbus::vehicle::neolix_edu::neolix_edu_controller
  modules::canbus::vehicle::neolix_edu::neolix_edu_message_manager
  modules::canbus::vehicle::abstract_vehicle_factory
)
add_library(modules::canbus::vehicle::neolix_edu::neolix_edu_vehicle_factory  ALIAS   modules_canbus_vehicle_neolix_edu_neolix_edu_vehicle_factory)

add_library(modules_canbus_vehicle_neolix_edu_neolix_edu_message_manager  SHARED
  neolix_edu_message_manager.cc
)
set_target_properties(modules_canbus_vehicle_neolix_edu_neolix_edu_message_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_neolix_edu_neolix_edu_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::neolix_edu::protocol::canbus_neolix_edu_protocol
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::neolix_edu::neolix_edu_message_manager  ALIAS   modules_canbus_vehicle_neolix_edu_neolix_edu_message_manager)

add_library(modules_canbus_vehicle_neolix_edu_neolix_edu_controller  SHARED
  neolix_edu_controller.cc
)
set_target_properties(modules_canbus_vehicle_neolix_edu_neolix_edu_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_neolix_edu_neolix_edu_controller
  modules::canbus::vehicle::neolix_edu::neolix_edu_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::vehicle_controller_base
  modules::canbus::vehicle::neolix_edu::protocol::canbus_neolix_edu_protocol
  modules::drivers::canbus::can_comm::can_sender
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::neolix_edu::neolix_edu_controller  ALIAS   modules_canbus_vehicle_neolix_edu_neolix_edu_controller)

