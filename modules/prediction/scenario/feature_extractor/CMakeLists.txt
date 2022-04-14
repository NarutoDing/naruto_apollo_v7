cmake_minimum_required(VERSION 3.16)

project(modules_prediction_scenario_feature_extractor)
message("${Green} [info] modules_prediction_scenario_feature_extractor cmakelist ${ColourReset}")

add_library(modules_prediction_scenario_feature_extractor_feature_extractor  SHARED
  feature_extractor.cc
)
set_target_properties(modules_prediction_scenario_feature_extractor_feature_extractor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_scenario_feature_extractor_feature_extractor
  modules::prediction::container::container_manager
)
add_library(modules::prediction::scenario::feature_extractor::feature_extractor  ALIAS   modules_prediction_scenario_feature_extractor_feature_extractor)

