cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_stop_sign_unprotected)
message("${Green} [info] modules_planning_scenarios_stop_sign_unprotected cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_stop_sign_unprotected_stop_sign_unprotected_scenario  SHARED
  stage_creep.cc
  stage_intersection_cruise.cc
  stage_pre_stop.cc
  stage_stop.cc
  stop_sign_unprotected_scenario.cc
)
set_target_properties(modules_planning_scenarios_stop_sign_unprotected_stop_sign_unprotected_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_stop_sign_unprotected_stop_sign_unprotected_scenario
  cyber::common::log
  modules::common::util::util
  modules::common::util::factory
  modules::planning::common::util::util_lib
  modules::planning::proto::planning_cc_proto
  modules::planning::scenarios::scenario
  modules::planning::scenarios::common::stage_intersection_cruise_impl
  modules::planning::scenarios::util::scenario_util_lib
  modules::planning::tasks::deciders::creep_decider::creep_decider
  ${gflags_LIBRARIES}
  ${eigen}
)
add_library(modules::planning::scenarios::stop_sign::unprotected::stop_sign_unprotected_scenario  ALIAS   modules_planning_scenarios_stop_sign_unprotected_stop_sign_unprotected_scenario)

