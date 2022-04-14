cmake_minimum_required(VERSION 3.16)

project(modules_canbus)
message("${Green} [info] modules_canbus cmakelist ${ColourReset}")

add_library(modules_canbus_canbus_component_lib  SHARED
  canbus_component.cc
)
set_target_properties(modules_canbus_canbus_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_canbus_component_lib
  cyber::cyber
  modules::canbus::common::canbus_common
  modules::canbus::vehicle::vehicle_factory
  modules::common::adapters::adapter_gflags
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::drivers::canbus::can_client::can_client
  modules::drivers::canbus::can_client::can_client_factory
  modules::drivers::canbus::can_comm::can_receiver
  modules::drivers::canbus::can_comm::can_sender
  modules::guardian::proto::guardian_cc_proto
  ${gflags_LIBRARIES}
)
add_library(modules::canbus::canbus_component_lib  ALIAS   modules_canbus_canbus_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libcanbus_component  SHARED
  ${virtual_cc}
)
set_target_properties(libcanbus_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libcanbus_component
  modules::canbus::canbus_component_lib
)
