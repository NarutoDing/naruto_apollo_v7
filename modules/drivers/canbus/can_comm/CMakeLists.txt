cmake_minimum_required(VERSION 3.16)

project(modules_drivers_canbus_can_comm)
message("${Green} [info] modules_drivers_canbus_can_comm cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_canbus_can_comm_can_receiver  SHARED
  ${virtual_cc}
  can_receiver.h
)
set_target_properties(modules_drivers_canbus_can_comm_can_receiver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_can_comm_can_receiver
  modules::common::proto::error_code_cc_proto
  modules::drivers::canbus::can_client::can_client
  modules::drivers::canbus::can_comm::message_manager_base
)
add_library(modules::drivers::canbus::can_comm::can_receiver  ALIAS   modules_drivers_canbus_can_comm_can_receiver)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_canbus_can_comm_can_sender  SHARED
  ${virtual_cc}
  can_sender.h
)
set_target_properties(modules_drivers_canbus_can_comm_can_sender  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_can_comm_can_sender
  modules::common::proto::error_code_cc_proto
  modules::drivers::canbus::can_client::can_client
  modules::drivers::canbus::can_comm::message_manager_base
  
)
add_library(modules::drivers::canbus::can_comm::can_sender  ALIAS   modules_drivers_canbus_can_comm_can_sender)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_canbus_can_comm_message_manager_base  SHARED
  ${virtual_cc}
  message_manager.h
)
set_target_properties(modules_drivers_canbus_can_comm_message_manager_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_can_comm_message_manager_base
  cyber::common::log
  cyber::time::time
  modules::common::proto::error_code_cc_proto
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::drivers::canbus::can_comm::message_manager_base  ALIAS   modules_drivers_canbus_can_comm_message_manager_base)

