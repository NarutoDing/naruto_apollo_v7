cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_devkit)
message("${Green} [info] modules_canbus_vehicle_devkit cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_devkit_devkit_vehicle_factory  SHARED
  devkit_vehicle_factory.cc
)
set_target_properties(modules_canbus_vehicle_devkit_devkit_vehicle_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_devkit_vehicle_factory
  modules::canbus::vehicle::devkit::devkit_controller
  modules::canbus::vehicle::devkit::devkit_message_manager
  modules::canbus::vehicle::abstract_vehicle_factory
)
add_library(modules::canbus::vehicle::devkit::devkit_vehicle_factory  ALIAS   modules_canbus_vehicle_devkit_devkit_vehicle_factory)

add_library(modules_canbus_vehicle_devkit_devkit_message_manager  SHARED
  devkit_message_manager.cc
)
set_target_properties(modules_canbus_vehicle_devkit_devkit_message_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_devkit_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::devkit::protocol::canbus_devkit_protocol
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::devkit_message_manager  ALIAS   modules_canbus_vehicle_devkit_devkit_message_manager)

add_library(modules_canbus_vehicle_devkit_devkit_controller  SHARED
  devkit_controller.cc
)
set_target_properties(modules_canbus_vehicle_devkit_devkit_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_devkit_controller
  modules::canbus::vehicle::devkit::devkit_message_manager
  modules::canbus::common::canbus_common
  modules::canbus::proto::canbus_conf_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::canbus::proto::vehicle_parameter_cc_proto
  modules::canbus::vehicle::vehicle_controller_base
  modules::canbus::vehicle::devkit::protocol::canbus_devkit_protocol
  modules::common::proto::error_code_cc_proto
  modules::control::proto::control_cmd_cc_proto
)
add_library(modules::canbus::vehicle::devkit::devkit_controller  ALIAS   modules_canbus_vehicle_devkit_devkit_controller)

