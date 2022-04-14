cmake_minimum_required(VERSION 3.16)

project(modules_prediction_scenario_interaction_filter)
message("${Green} [info] modules_prediction_scenario_interaction_filter cmakelist ${ColourReset}")

add_library(modules_prediction_scenario_interaction_filter_interaction_filter  SHARED
  interaction_filter.cc
)
set_target_properties(modules_prediction_scenario_interaction_filter_interaction_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_scenario_interaction_filter_interaction_filter
  modules::prediction::common::environment_features
  modules::prediction::container::container_manager
  modules::prediction::container::obstacles::obstacle_clusters
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::container::pose::pose_container
  modules::prediction::scenario::scenario_features::scenario_features
  modules::prediction::scenario::scenario_features::cruise_scenario_features
)
add_library(modules::prediction::scenario::interaction_filter::interaction_filter  ALIAS   modules_prediction_scenario_interaction_filter_interaction_filter)

