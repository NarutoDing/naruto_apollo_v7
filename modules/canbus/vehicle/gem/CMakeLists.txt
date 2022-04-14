cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_gem)
message("${Green} [info] modules_canbus_vehicle_gem cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_gem_gem_vehicle_factory  SHARED
  gem_vehicle_factory.cc
)
set_target_properties(modules_canbus_vehicle_gem_gem_vehicle_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_gem_gem_vehicle_factory
  modules::canbus::vehicle::gem::gem_controller
  modules::canbus::vehicle::gem::gem_message_manager
  modules::canbus::proto::canbus_conf_cc_proto
  modules::canbus::proto::vehicle_parameter_cc_proto
  modules::canbus::vehicle::abstract_vehicle_factory
)
add_library(modules::canbus::vehicle::gem::gem_vehicle_factory  ALIAS   modules_canbus_vehicle_gem_gem_vehicle_factory)

add_library(modules_canbus_vehicle_gem_gem_message_manager  SHARED
  gem_message_manager.cc
)
set_target_properties(modules_canbus_vehicle_gem_gem_message_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_gem_gem_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::gem::protocol::canbus_gem_protocol
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::gem::gem_message_manager  ALIAS   modules_canbus_vehicle_gem_gem_message_manager)

add_library(modules_canbus_vehicle_gem_gem_controller  SHARED
  gem_controller.cc
)
set_target_properties(modules_canbus_vehicle_gem_gem_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_gem_gem_controller
  modules::canbus::vehicle::gem::gem_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::vehicle_controller_base
  modules::canbus::vehicle::gem::protocol::canbus_gem_protocol
  modules::drivers::canbus::can_comm::can_sender
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::gem::gem_controller  ALIAS   modules_canbus_vehicle_gem_gem_controller)

