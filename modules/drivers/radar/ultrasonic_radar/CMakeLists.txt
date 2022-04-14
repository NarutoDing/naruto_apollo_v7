cmake_minimum_required(VERSION 3.16)

project(modules_drivers_radar_ultrasonic_radar)
message("${Green} [info] modules_drivers_radar_ultrasonic_radar cmakelist ${ColourReset}")

add_library(modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_message_manager  SHARED
  ultrasonic_radar_message_manager.cc
)
set_target_properties(modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_message_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_message_manager
  modules::common::proto::header_cc_proto
  modules::common::util::message_util
  modules::drivers::canbus::sensor_gflags
  modules::drivers::canbus::can_client::can_client_factory
  modules::drivers::canbus::can_comm::can_sender
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::proto::ultrasonic_radar_cc_proto
)
add_library(modules::drivers::radar::ultrasonic_radar::ultrasonic_radar_message_manager  ALIAS   modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_message_manager)

add_library(modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_canbus_lib  SHARED
  ultrasonic_radar_canbus.cc
)
set_target_properties(modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_canbus_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_canbus_lib
  modules::drivers::radar::ultrasonic_radar::ultrasonic_radar_message_manager
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::drivers::canbus::sensor_gflags
  modules::drivers::canbus::can_client::can_client_factory
  modules::drivers::canbus::can_comm::can_receiver
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::proto::sensor_canbus_conf_cc_proto
  modules::drivers::radar::ultrasonic_radar::proto::ultrasonic_radar_conf_cc_proto
)
add_library(modules::drivers::radar::ultrasonic_radar::ultrasonic_radar_canbus_lib  ALIAS   modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_canbus_lib)

add_library(modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_canbus_component_lib  SHARED
  ultrasonic_radar_canbus_component.cc
)
set_target_properties(modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_canbus_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_canbus_component_lib
  modules::drivers::radar::ultrasonic_radar::ultrasonic_radar_canbus_lib
  modules::common::adapters::adapter_gflags
  modules::drivers::proto::ultrasonic_radar_cc_proto
)
add_library(modules::drivers::radar::ultrasonic_radar::ultrasonic_radar_canbus_component_lib  ALIAS   modules_drivers_radar_ultrasonic_radar_ultrasonic_radar_canbus_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libultrasonic_radar_canbus_component  SHARED
  ${virtual_cc}
)
set_target_properties(libultrasonic_radar_canbus_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libultrasonic_radar_canbus_component
  modules::drivers::radar::ultrasonic_radar::ultrasonic_radar_canbus_component_lib
)
