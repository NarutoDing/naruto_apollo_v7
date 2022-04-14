cmake_minimum_required(VERSION 3.16)

project(modules_routing_core)
message("${Green} [info] modules_routing_core cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_routing_core_core  SHARED
  ${virtual_cc}
)
set_target_properties(modules_routing_core_core  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_core_core
  modules::routing::core::routing_navigator
)
add_library(modules::routing::core::core  ALIAS   modules_routing_core_core)

add_library(modules_routing_core_routing_navigator  SHARED
  navigator.cc
)
set_target_properties(modules_routing_core_routing_navigator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_core_routing_navigator
  modules::routing::core::routing_black_list_range_generator
  modules::routing::core::routing_result_generator
  modules::common::util::util
  modules::routing::strategy::strategy
)
add_library(modules::routing::core::routing_navigator  ALIAS   modules_routing_core_routing_navigator)

add_library(modules_routing_core_routing_black_list_range_generator  SHARED
  black_list_range_generator.cc
)
set_target_properties(modules_routing_core_routing_black_list_range_generator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_core_routing_black_list_range_generator
  modules::routing::graph::graph
)
add_library(modules::routing::core::routing_black_list_range_generator  ALIAS   modules_routing_core_routing_black_list_range_generator)

add_library(modules_routing_core_routing_result_generator  SHARED
  result_generator.cc
)
set_target_properties(modules_routing_core_routing_result_generator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_core_routing_result_generator
  modules::routing::graph::graph
)
add_library(modules::routing::core::routing_result_generator  ALIAS   modules_routing_core_routing_result_generator)

