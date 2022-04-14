cmake_minimum_required(VERSION 3.16)

project(cyber_tools_cyber_monitor)
message("${Green} [info] cyber_tools_cyber_monitor cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_tools_cyber_monitor_cyber_topology_message  SHARED
  ${virtual_cc}
  cyber_topology_message.h
)
set_target_properties(cyber_tools_cyber_monitor_cyber_topology_message  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_monitor_cyber_topology_message
  cyber::tools::cyber_monitor::renderable_message
)
add_library(cyber::tools::cyber_monitor::cyber_topology_message  ALIAS   cyber_tools_cyber_monitor_cyber_topology_message)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_tools_cyber_monitor_general_channel_message  SHARED
  ${virtual_cc}
  general_channel_message.h
)
set_target_properties(cyber_tools_cyber_monitor_general_channel_message  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_monitor_general_channel_message
  cyber::tools::cyber_monitor::general_message
  cyber::tools::cyber_monitor::general_message_base
  cyber::tools::cyber_monitor::screen
  cyber::cyber
  cyber::message::raw_message
  cyber::record::record_message
)
add_library(cyber::tools::cyber_monitor::general_channel_message  ALIAS   cyber_tools_cyber_monitor_general_channel_message)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_tools_cyber_monitor_general_message  SHARED
  ${virtual_cc}
  general_message.h
)
set_target_properties(cyber_tools_cyber_monitor_general_message  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_monitor_general_message
  cyber::tools::cyber_monitor::general_message_base
  cyber::cyber
  cyber::message::raw_message
)
add_library(cyber::tools::cyber_monitor::general_message  ALIAS   cyber_tools_cyber_monitor_general_message)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_tools_cyber_monitor_general_message_base  SHARED
  ${virtual_cc}
  general_message_base.h
)
set_target_properties(cyber_tools_cyber_monitor_general_message_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_monitor_general_message_base
  cyber::tools::cyber_monitor::renderable_message
)
add_library(cyber::tools::cyber_monitor::general_message_base  ALIAS   cyber_tools_cyber_monitor_general_message_base)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_tools_cyber_monitor_renderable_message  SHARED
  ${virtual_cc}
  renderable_message.h
)
set_target_properties(cyber_tools_cyber_monitor_renderable_message  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_monitor_renderable_message
  cyber::tools::cyber_monitor::screen
)
add_library(cyber::tools::cyber_monitor::renderable_message  ALIAS   cyber_tools_cyber_monitor_renderable_message)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_tools_cyber_monitor_screen  SHARED
  ${virtual_cc}
  screen.h
)
set_target_properties(cyber_tools_cyber_monitor_screen  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::tools::cyber_monitor::screen  ALIAS   cyber_tools_cyber_monitor_screen)

add_executable(cyber_monitor
  cyber_topology_message.cc
  general_channel_message.cc
  general_message.cc
  general_message_base.cc
  main.cc
  renderable_message.cc
  screen.cc
)
target_link_libraries(cyber_monitor
  cyber::tools::cyber_monitor::cyber_topology_message
  cyber::tools::cyber_monitor::general_channel_message
  cyber::tools::cyber_monitor::screen
  cyber::init
  cyber::service_discovery::topology_manager
  ${CURSES_LIBRARIES}
)
