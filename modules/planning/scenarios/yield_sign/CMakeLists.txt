cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_yield_sign)
message("${Green} [info] modules_planning_scenarios_yield_sign cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_yield_sign_yield_sign_scenario  SHARED
  stage_approach.cc
  stage_creep.cc
  yield_sign_scenario.cc
)
set_target_properties(modules_planning_scenarios_yield_sign_yield_sign_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_yield_sign_yield_sign_scenario
  cyber::common::log
  modules::common::util::factory
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::common::planning_common
  modules::planning::common::util::common_lib
  modules::planning::common::util::util_lib
  modules::planning::proto::planning_cc_proto
  modules::planning::scenarios::scenario
  modules::planning::scenarios::util::scenario_util_lib
  ${gflags_LIBRARIES}
  ${eigen}
)
add_library(modules::planning::scenarios::yield_sign::yield_sign_scenario  ALIAS   modules_planning_scenarios_yield_sign_yield_sign_scenario)

