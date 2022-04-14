cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_util)
message("${Green} [info] modules_planning_scenarios_util cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_util_scenario_util_lib  SHARED
  util.cc
)
set_target_properties(modules_planning_scenarios_util_scenario_util_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_util_scenario_util_lib
  cyber::common::log
  modules::common::util::map_util
  modules::planning::common::planning_common
)
add_library(modules::planning::scenarios::util::scenario_util_lib  ALIAS   modules_planning_scenarios_util_scenario_util_lib)

