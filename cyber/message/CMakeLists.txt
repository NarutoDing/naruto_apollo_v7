cmake_minimum_required(VERSION 3.16)

project(cyber_message)
message("${Green} [info] cyber_message cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_message_message_header  SHARED
  ${virtual_cc}
  message_header.h
)
set_target_properties(cyber_message_message_header  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::message::message_header  ALIAS   cyber_message_message_header)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_message_message_traits  SHARED
  ${virtual_cc}
  message_traits.h
)
set_target_properties(cyber_message_message_traits  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_message_message_traits
  cyber::message::message_header
  cyber::message::protobuf_traits
  cyber::message::py_message_traits
  cyber::message::raw_message_traits
  cyber::base::macros
)
add_library(cyber::message::message_traits  ALIAS   cyber_message_message_traits)

add_library(cyber_message_protobuf_factory  SHARED
  protobuf_factory.cc
)
set_target_properties(cyber_message_protobuf_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_message_protobuf_factory
  cyber::common::log
  cyber::common::macros
  cyber::proto::proto_desc_cc_proto
)
add_library(cyber::message::protobuf_factory  ALIAS   cyber_message_protobuf_factory)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_message_protobuf_traits  SHARED
  ${virtual_cc}
  protobuf_traits.h
)
set_target_properties(cyber_message_protobuf_traits  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_message_protobuf_traits
  cyber::message::protobuf_factory
)
add_library(cyber::message::protobuf_traits  ALIAS   cyber_message_protobuf_traits)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_message_py_message  SHARED
  ${virtual_cc}
  py_message.h
)
set_target_properties(cyber_message_py_message  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_message_py_message
  cyber::message::protobuf_factory
)
add_library(cyber::message::py_message  ALIAS   cyber_message_py_message)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_message_py_message_traits  SHARED
  ${virtual_cc}
  py_message_traits.h
)
set_target_properties(cyber_message_py_message_traits  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_message_py_message_traits
  cyber::message::protobuf_factory
  cyber::message::py_message
)
add_library(cyber::message::py_message_traits  ALIAS   cyber_message_py_message_traits)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_message_raw_message  SHARED
  ${virtual_cc}
  raw_message.h
)
set_target_properties(cyber_message_raw_message  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_message_raw_message
  cyber::message::protobuf_factory
)
add_library(cyber::message::raw_message  ALIAS   cyber_message_raw_message)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_message_raw_message_traits  SHARED
  ${virtual_cc}
  raw_message_traits.h
)
set_target_properties(cyber_message_raw_message_traits  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_message_raw_message_traits
  cyber::message::protobuf_factory
  cyber::message::raw_message
)
add_library(cyber::message::raw_message_traits  ALIAS   cyber_message_raw_message_traits)

