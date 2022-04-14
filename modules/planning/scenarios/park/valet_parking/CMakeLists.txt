cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_park_valet_parking)
message("${Green} [info] modules_planning_scenarios_park_valet_parking cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_park_valet_parking_valet_parking  SHARED
  stage_approaching_parking_spot.cc
  stage_parking.cc
  valet_parking_scenario.cc
)
set_target_properties(modules_planning_scenarios_park_valet_parking_valet_parking  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_park_valet_parking_valet_parking
  cyber::common::log
  modules::planning::proto::planning_cc_proto
  modules::planning::scenarios::scenario
)
add_library(modules::planning::scenarios::park::valet_parking::valet_parking  ALIAS   modules_planning_scenarios_park_valet_parking_valet_parking)

