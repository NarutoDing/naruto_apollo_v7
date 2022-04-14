cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_park_pull_over)
message("${Green} [info] modules_planning_scenarios_park_pull_over cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_park_pull_over_pull_over_scenario  SHARED
  pull_over_scenario.cc
  stage_approach.cc
  stage_retry_approach_parking.cc
  stage_retry_parking.cc
)
set_target_properties(modules_planning_scenarios_park_pull_over_pull_over_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_park_pull_over_pull_over_scenario
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
  
  ${cuda}
)
add_library(modules::planning::scenarios::park::pull_over::pull_over_scenario  ALIAS   modules_planning_scenarios_park_pull_over_pull_over_scenario)

