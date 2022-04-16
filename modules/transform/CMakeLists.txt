cmake_minimum_required(VERSION 3.16)

project(modules_transform)
message("${Green} [info] modules_transform cmakelist ${ColourReset}")

add_library(modules_transform_buffer  SHARED
  buffer.cc
)
set_target_properties(modules_transform_buffer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_transform_buffer
  modules::transform::buffer_interface
  cyber::cyber
  cyber::node::node
  modules::common::adapters::adapter_gflags
  ${tf2}
  ${absl}
)
add_library(modules::transform::buffer  ALIAS   modules_transform_buffer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_transform_buffer_interface  SHARED
  ${virtual_cc}
  buffer_interface.h
)
set_target_properties(modules_transform_buffer_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_transform_buffer_interface
  modules::transform::proto::transform_cc_proto
)
add_library(modules::transform::buffer_interface  ALIAS   modules_transform_buffer_interface)

add_library(modules_transform_transform_broadcaster  SHARED
  transform_broadcaster.cc
)
set_target_properties(modules_transform_transform_broadcaster  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_transform_transform_broadcaster
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::transform::proto::transform_cc_proto
)
add_library(modules::transform::transform_broadcaster  ALIAS   modules_transform_transform_broadcaster)

add_library(modules_transform_static_transform_component_lib  SHARED
  static_transform_component.cc
)
set_target_properties(modules_transform_static_transform_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_transform_static_transform_component_lib
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::transform::proto::static_transform_conf_cc_proto
  modules::transform::proto::transform_cc_proto
  ${yaml}
)
add_library(modules::transform::static_transform_component_lib  ALIAS   modules_transform_static_transform_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libstatic_transform_component  SHARED
  ${virtual_cc}
)
set_target_properties(libstatic_transform_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libstatic_transform_component
  modules::transform::static_transform_component_lib
)
