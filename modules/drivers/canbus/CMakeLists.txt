cmake_minimum_required(VERSION 3.16)

project(modules_drivers_canbus)
message("${Green} [info] modules_drivers_canbus cmakelist ${ColourReset}")

add_library(modules_drivers_canbus_sensor_gflags  SHARED
  sensor_gflags.cc
)
set_target_properties(modules_drivers_canbus_sensor_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_sensor_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::drivers::canbus::sensor_gflags  ALIAS   modules_drivers_canbus_sensor_gflags)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_canbus_sensor_canbus_lib  SHARED
  ${virtual_cc}
  sensor_canbus.h
)
set_target_properties(modules_drivers_canbus_sensor_canbus_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_sensor_canbus_lib
  modules::drivers::canbus::sensor_gflags
  modules::common::monitor_log::monitor_log
  modules::drivers::canbus::can_client::can_client_factory
  modules::drivers::canbus::can_comm::can_receiver
  modules::drivers::canbus::can_comm::message_manager_base
)
add_library(modules::drivers::canbus::sensor_canbus_lib  ALIAS   modules_drivers_canbus_sensor_canbus_lib)

