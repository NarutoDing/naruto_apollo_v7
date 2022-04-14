cmake_minimum_required(VERSION 3.16)

project(modules_routing)
message("${Green} [info] modules_routing cmakelist ${ColourReset}")

add_library(modules_routing_routing  SHARED
  routing.cc
)
set_target_properties(modules_routing_routing  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_routing
  modules::common::adapters::adapter_gflags
  modules::common::monitor_log::monitor_log
  modules::common::util::point_factory
  modules::map::hdmap::hdmap_util
  modules::routing::core::core
  modules::routing::proto::routing_config_cc_proto
)
add_library(modules::routing::routing  ALIAS   modules_routing_routing)

add_library(modules_routing_routing_component_lib  SHARED
  routing_component.cc
)
set_target_properties(modules_routing_routing_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_routing_component_lib
  modules::routing::routing
  cyber::time::clock
)
add_library(modules::routing::routing_component_lib  ALIAS   modules_routing_routing_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(librouting_component  SHARED
  ${virtual_cc}
)
set_target_properties(librouting_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(librouting_component
  modules::routing::routing_component_lib
)
