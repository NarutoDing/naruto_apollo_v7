cmake_minimum_required(VERSION 3.16)

project(modules_prediction_predictor_interaction)
message("${Green} [info] modules_prediction_predictor_interaction cmakelist ${ColourReset}")

add_library(modules_prediction_predictor_interaction_interaction_predictor  SHARED
  interaction_predictor.cc
)
set_target_properties(modules_prediction_predictor_interaction_interaction_predictor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_interaction_interaction_predictor
  modules::common::adapters::proto::adapter_config_cc_proto
  modules::prediction::common::feature_output
  modules::prediction::common::prediction_util
  modules::prediction::predictor::sequence::sequence_predictor
)
add_library(modules::prediction::predictor::interaction::interaction_predictor  ALIAS   modules_prediction_predictor_interaction_interaction_predictor)

