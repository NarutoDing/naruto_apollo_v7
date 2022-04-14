cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_emergency_emergency_pull_over)
message("${Green} [info] modules_planning_scenarios_emergency_emergency_pull_over cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_emergency_emergency_pull_over_emergency_pull_over_scenario  SHARED
  emergency_pull_over_scenario.cc
  stage_approach.cc
  stage_slow_down.cc
  stage_standby.cc
)
set_target_properties(modules_planning_scenarios_emergency_emergency_pull_over_emergency_pull_over_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_emergency_emergency_pull_over_emergency_pull_over_scenario
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
add_library(modules::planning::scenarios::emergency::emergency_pull_over::emergency_pull_over_scenario  ALIAS   modules_planning_scenarios_emergency_emergency_pull_over_emergency_pull_over_scenario)

