cmake_minimum_required(VERSION 3.16)

project(modules_prediction_scenario)
message("${Green} [info] modules_prediction_scenario cmakelist ${ColourReset}")

add_library(modules_prediction_scenario_scenario_manager  SHARED
  scenario_manager.cc
)
set_target_properties(modules_prediction_scenario_scenario_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_scenario_scenario_manager
  modules::prediction::scenario::analyzer::scenario_analyzer
  modules::prediction::scenario::feature_extractor::feature_extractor
  modules::prediction::scenario::interaction_filter::interaction_filter
  modules::prediction::scenario::prioritization::obstacles_prioritizer
  modules::prediction::scenario::right_of_way::right_of_way
)
add_library(modules::prediction::scenario::scenario_manager  ALIAS   modules_prediction_scenario_scenario_manager)

