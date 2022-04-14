cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_dead_end_deadend_turnaround)
message("${Green} [info] modules_planning_scenarios_dead_end_deadend_turnaround cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_dead_end_deadend_turnaround_deadend_turnaround  SHARED
  stage_approaching_turning_point.cc
  stage_turning.cc
  deadend_turnaround_scenario.cc
)
set_target_properties(modules_planning_scenarios_dead_end_deadend_turnaround_deadend_turnaround  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_dead_end_deadend_turnaround_deadend_turnaround
  cyber::common::log
  modules::planning::proto::planning_cc_proto
  modules::planning::scenarios::scenario
)
add_library(modules::planning::scenarios::dead_end::deadend_turnaround::deadend_turnaround  ALIAS   modules_planning_scenarios_dead_end_deadend_turnaround_deadend_turnaround)

