cmake_minimum_required(VERSION 3.16)

project(modules_bridge)
message("${Green} [info] modules_bridge cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_bridge_udp_bridge  SHARED
  ${virtual_cc}
)
set_target_properties(modules_bridge_udp_bridge  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_bridge_udp_bridge
  cyber::cyber
  modules::bridge::common::bridge_gflags
  modules::bridge::common::bridge_header
  modules::bridge::common::bridge_proto_diser_buf_factory
  modules::bridge::common::bridge_proto_diserialized_buf
  modules::bridge::common::bridge_proto_serialized_buf
  modules::bridge::common::macro
  modules::bridge::common::util
  modules::bridge::proto::udp_bridge_remote_info_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::monitor_log::monitor_log
  modules::common::util::util
  modules::planning::proto::planning_cc_proto
  ${gflags_LIBRARIES}
)
add_library(modules::bridge::udp_bridge  ALIAS   modules_bridge_udp_bridge)

add_library(modules_bridge_udp_bridge_sender  SHARED
  udp_bridge_sender_component.cc
)
set_target_properties(modules_bridge_udp_bridge_sender  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_bridge_udp_bridge_sender
  modules::bridge::udp_bridge
)
add_library(modules::bridge::udp_bridge_sender  ALIAS   modules_bridge_udp_bridge_sender)

add_library(modules_bridge_udp_bridge_receiver  SHARED
  udp_bridge_receiver_component.cc
)
set_target_properties(modules_bridge_udp_bridge_receiver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_bridge_udp_bridge_receiver
  modules::bridge::udp_bridge
  modules::bridge::common::udp_listener
)
add_library(modules::bridge::udp_bridge_receiver  ALIAS   modules_bridge_udp_bridge_receiver)

add_library(modules_bridge_udp_bridge_multi_receiver  SHARED
  udp_bridge_multi_receiver_component.cc
)
set_target_properties(modules_bridge_udp_bridge_multi_receiver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_bridge_udp_bridge_multi_receiver
  modules::bridge::udp_bridge
  modules::bridge::common::udp_listener
)
add_library(modules::bridge::udp_bridge_multi_receiver  ALIAS   modules_bridge_udp_bridge_multi_receiver)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libudp_bridge_sender_component  SHARED
  ${virtual_cc}
)
set_target_properties(libudp_bridge_sender_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libudp_bridge_sender_component
  modules::bridge::udp_bridge_sender
)
set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libudp_bridge_receiver_component  SHARED
  ${virtual_cc}
)
set_target_properties(libudp_bridge_receiver_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libudp_bridge_receiver_component
  modules::bridge::udp_bridge_receiver
)
set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libudp_bridge_multi_receiver_component  SHARED
  ${virtual_cc}
)
set_target_properties(libudp_bridge_multi_receiver_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libudp_bridge_multi_receiver_component
  modules::bridge::udp_bridge_multi_receiver
)
