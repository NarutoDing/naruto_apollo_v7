cmake_minimum_required(VERSION 3.16)

project(modules_prediction_scenario_analyzer)
message("${Green} [info] modules_prediction_scenario_analyzer cmakelist ${ColourReset}")

add_library(modules_prediction_scenario_analyzer_scenario_analyzer  SHARED
  scenario_analyzer.cc
)
set_target_properties(modules_prediction_scenario_analyzer_scenario_analyzer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_scenario_analyzer_scenario_analyzer
  modules::prediction::scenario::scenario_features::cruise_scenario_features
  modules::prediction::scenario::scenario_features::junction_scenario_features
)
add_library(modules::prediction::scenario::analyzer::scenario_analyzer  ALIAS   modules_prediction_scenario_analyzer_scenario_analyzer)

