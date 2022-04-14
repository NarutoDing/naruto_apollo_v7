cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_park_and_go)
message("${Green} [info] modules_planning_scenarios_park_and_go cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_park_and_go_park_and_go_scenario  SHARED
  park_and_go_scenario.cc
  stage_adjust.cc
  stage_check.cc
  stage_cruise.cc
  stage_pre_cruise.cc
)
set_target_properties(modules_planning_scenarios_park_and_go_park_and_go_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_park_and_go_park_and_go_scenario
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
)
add_library(modules::planning::scenarios::park_and_go::park_and_go_scenario  ALIAS   modules_planning_scenarios_park_and_go_park_and_go_scenario)

