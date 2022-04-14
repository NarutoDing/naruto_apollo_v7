cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_narrow_street_u_turn)
message("${Green} [info] modules_planning_scenarios_narrow_street_u_turn cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_scenarios_narrow_street_u_turn_narrow_street_u_turn  SHARED
  ${virtual_cc}
)
set_target_properties(modules_planning_scenarios_narrow_street_u_turn_narrow_street_u_turn  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_narrow_street_u_turn_narrow_street_u_turn
  modules::planning::scenarios::narrow_street_u_turn::narrow_street_u_turn_scenario
)
add_library(modules::planning::scenarios::narrow_street_u_turn::narrow_street_u_turn  ALIAS   modules_planning_scenarios_narrow_street_u_turn_narrow_street_u_turn)

add_library(modules_planning_scenarios_narrow_street_u_turn_narrow_street_u_turn_scenario  SHARED
  narrow_street_u_turn_scenario.cc
)
set_target_properties(modules_planning_scenarios_narrow_street_u_turn_narrow_street_u_turn_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_narrow_street_u_turn_narrow_street_u_turn_scenario
  cyber::common::log
  modules::planning::proto::planning_cc_proto
  modules::planning::scenarios::scenario
)
add_library(modules::planning::scenarios::narrow_street_u_turn::narrow_street_u_turn_scenario  ALIAS   modules_planning_scenarios_narrow_street_u_turn_narrow_street_u_turn_scenario)

