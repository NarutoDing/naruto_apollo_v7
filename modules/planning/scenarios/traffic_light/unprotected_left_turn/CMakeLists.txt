cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_traffic_light_unprotected_left_turn)
message("${Green} [info] modules_planning_scenarios_traffic_light_unprotected_left_turn cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_traffic_light_unprotected_left_turn_traffic_light_unprotected_left_turn_scenario  SHARED
  stage_approach.cc
  stage_creep.cc
  stage_intersection_cruise.cc
  traffic_light_unprotected_left_turn_scenario.cc
)
set_target_properties(modules_planning_scenarios_traffic_light_unprotected_left_turn_traffic_light_unprotected_left_turn_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_traffic_light_unprotected_left_turn_traffic_light_unprotected_left_turn_scenario
  cyber::common::log
  modules::common::util::util
  modules::common::util::factory
  modules::planning::proto::planning_cc_proto
  modules::planning::scenarios::scenario
  modules::planning::scenarios::common::stage_intersection_cruise_impl
  modules::planning::tasks::deciders::creep_decider::creep_decider
  ${gflags_LIBRARIES}
  ${eigen}
  
  ${cuda}
)
add_library(modules::planning::scenarios::traffic_light::unprotected_left_turn::traffic_light_unprotected_left_turn_scenario  ALIAS   modules_planning_scenarios_traffic_light_unprotected_left_turn_traffic_light_unprotected_left_turn_scenario)

