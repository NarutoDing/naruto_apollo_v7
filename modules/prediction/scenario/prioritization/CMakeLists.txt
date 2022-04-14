cmake_minimum_required(VERSION 3.16)

project(modules_prediction_scenario_prioritization)
message("${Green} [info] modules_prediction_scenario_prioritization cmakelist ${ColourReset}")

add_library(modules_prediction_scenario_prioritization_obstacles_prioritizer  SHARED
  obstacles_prioritizer.cc
)
set_target_properties(modules_prediction_scenario_prioritization_obstacles_prioritizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_scenario_prioritization_obstacles_prioritizer
  modules::prediction::common::environment_features
  modules::prediction::container::container_manager
  modules::prediction::container::obstacles::obstacle_clusters
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::container::pose::pose_container
  modules::prediction::scenario::scenario_features::scenario_features
  modules::prediction::scenario::scenario_features::cruise_scenario_features
)
add_library(modules::prediction::scenario::prioritization::obstacles_prioritizer  ALIAS   modules_prediction_scenario_prioritization_obstacles_prioritizer)

