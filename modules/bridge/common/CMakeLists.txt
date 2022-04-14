cmake_minimum_required(VERSION 3.16)

project(modules_bridge_common)
message("${Green} [info] modules_bridge_common cmakelist ${ColourReset}")

add_library(modules_bridge_common_bridge_buffer  SHARED
  bridge_buffer.cc
)
set_target_properties(modules_bridge_common_bridge_buffer  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::bridge::common::bridge_buffer  ALIAS   modules_bridge_common_bridge_buffer)

add_library(modules_bridge_common_bridge_gflags  SHARED
  bridge_gflags.cc
)
set_target_properties(modules_bridge_common_bridge_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_bridge_common_bridge_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::bridge::common::bridge_gflags  ALIAS   modules_bridge_common_bridge_gflags)

add_library(modules_bridge_common_util  SHARED
  util.cc
)
set_target_properties(modules_bridge_common_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_bridge_common_util
  modules::bridge::common::bridge_buffer
  modules::bridge::common::macro
)
add_library(modules::bridge::common::util  ALIAS   modules_bridge_common_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_bridge_common_macro  SHARED
  ${virtual_cc}
  macro.h
)
set_target_properties(modules_bridge_common_macro  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::bridge::common::macro  ALIAS   modules_bridge_common_macro)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_bridge_common_bridge_proto_serialized_buf  SHARED
  ${virtual_cc}
  bridge_proto_serialized_buf.h
)
set_target_properties(modules_bridge_common_bridge_proto_serialized_buf  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::bridge::common::bridge_proto_serialized_buf  ALIAS   modules_bridge_common_bridge_proto_serialized_buf)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_bridge_common_bridge_proto_diserialized_buf  SHARED
  ${virtual_cc}
  bridge_proto_diserialized_buf.h
)
set_target_properties(modules_bridge_common_bridge_proto_diserialized_buf  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::bridge::common::bridge_proto_diserialized_buf  ALIAS   modules_bridge_common_bridge_proto_diserialized_buf)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_bridge_common_bridge_proto_diser_buf_factory  SHARED
  ${virtual_cc}
  bridge_proto_diser_buf_factory.h
)
set_target_properties(modules_bridge_common_bridge_proto_diser_buf_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_bridge_common_bridge_proto_diser_buf_factory
  modules::common::adapters::adapter_gflags
)
add_library(modules::bridge::common::bridge_proto_diser_buf_factory  ALIAS   modules_bridge_common_bridge_proto_diser_buf_factory)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_bridge_common_udp_listener  SHARED
  ${virtual_cc}
  udp_listener.h
)
set_target_properties(modules_bridge_common_udp_listener  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::bridge::common::udp_listener  ALIAS   modules_bridge_common_udp_listener)

add_library(modules_bridge_common_bridge_header  SHARED
  bridge_header.cc
)
set_target_properties(modules_bridge_common_bridge_header  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::bridge::common::bridge_header  ALIAS   modules_bridge_common_bridge_header)

