cmake_minimum_required(VERSION 3.16)

project(modules_routing_strategy)
message("${Green} [info] modules_routing_strategy cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_routing_strategy_strategy  SHARED
  ${virtual_cc}
)
set_target_properties(modules_routing_strategy_strategy  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_strategy_strategy
  modules::routing::strategy::routing_a_star_strategy
)
add_library(modules::routing::strategy::strategy  ALIAS   modules_routing_strategy_strategy)

add_library(modules_routing_strategy_routing_a_star_strategy  SHARED
  a_star_strategy.cc
)
set_target_properties(modules_routing_strategy_routing_a_star_strategy  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_strategy_routing_a_star_strategy
  modules::routing::graph::graph
)
add_library(modules::routing::strategy::routing_a_star_strategy  ALIAS   modules_routing_strategy_routing_a_star_strategy)

