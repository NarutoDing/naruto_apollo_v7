cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_bare_intersection_unprotected)
message("${Green} [info] modules_planning_scenarios_bare_intersection_unprotected cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_bare_intersection_unprotected_bare_intersection_unprotected_scenario  SHARED
  bare_intersection_unprotected_scenario.cc
  stage_approach.cc
  stage_intersection_cruise.cc
)
set_target_properties(modules_planning_scenarios_bare_intersection_unprotected_bare_intersection_unprotected_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_bare_intersection_unprotected_bare_intersection_unprotected_scenario
  cyber::common::log
  modules::common::util::util
  modules::common::util::factory
  modules::planning::common::util::common_lib
  modules::planning::proto::planning_cc_proto
  modules::planning::scenarios::scenario
  modules::planning::scenarios::common::stage_intersection_cruise_impl
  modules::planning::tasks::deciders::creep_decider::creep_decider
  ${gflags_LIBRARIES}
  ${eigen}
  
  ${cuda}
)
add_library(modules::planning::scenarios::bare_intersection::unprotected::bare_intersection_unprotected_scenario  ALIAS   modules_planning_scenarios_bare_intersection_unprotected_bare_intersection_unprotected_scenario)

