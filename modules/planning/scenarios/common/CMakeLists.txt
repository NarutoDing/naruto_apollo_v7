cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_common)
message("${Green} [info] modules_planning_scenarios_common cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_common_stage_intersection_cruise_impl  SHARED
  stage_intersection_cruise_impl.cc
)
set_target_properties(modules_planning_scenarios_common_stage_intersection_cruise_impl  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_common_stage_intersection_cruise_impl
  modules::planning::common::planning_common
  modules::planning::common::util::util_lib
  modules::planning::scenarios::util::scenario_util_lib
)
add_library(modules::planning::scenarios::common::stage_intersection_cruise_impl  ALIAS   modules_planning_scenarios_common_stage_intersection_cruise_impl)

