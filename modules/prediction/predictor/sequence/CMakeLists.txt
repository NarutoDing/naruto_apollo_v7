cmake_minimum_required(VERSION 3.16)

project(modules_prediction_predictor_sequence)
message("${Green} [info] modules_prediction_predictor_sequence cmakelist ${ColourReset}")

add_library(modules_prediction_predictor_sequence_sequence_predictor  SHARED
  sequence_predictor.cc
)
set_target_properties(modules_prediction_predictor_sequence_sequence_predictor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_sequence_sequence_predictor
  modules::prediction::container::container_manager
  modules::prediction::predictor::predictor
)
add_library(modules::prediction::predictor::sequence::sequence_predictor  ALIAS   modules_prediction_predictor_sequence_sequence_predictor)

