cmake_minimum_required(VERSION 3.16)

project(modules_drivers_canbus_can_client)
message("${Green} [info] modules_drivers_canbus_can_client cmakelist ${ColourReset}")

add_library(modules_drivers_canbus_can_client_can_client_factory  SHARED
  can_client_factory.cc
)
set_target_properties(modules_drivers_canbus_can_client_can_client_factory  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::canbus::can_client::can_client_factory  ALIAS   modules_drivers_canbus_can_client_can_client_factory)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_canbus_can_client_can_client  SHARED
  ${virtual_cc}
  can_client.h
)
set_target_properties(modules_drivers_canbus_can_client_can_client  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_can_client_can_client
  modules::common::util::util
  modules::drivers::canbus::common::canbus_common
  modules::drivers::canbus::proto::can_card_parameter_cc_proto
)
add_library(modules::drivers::canbus::can_client::can_client  ALIAS   modules_drivers_canbus_can_client_can_client)

add_executable(can_client_tool
  can_client_tool.cc
)
target_link_libraries(can_client_tool
  cyber::time::time
  modules::drivers::canbus::can_client::can_client_factory
  modules::drivers::canbus::proto::can_card_parameter_cc_proto
  ${gflags_LIBRARIES}
)
