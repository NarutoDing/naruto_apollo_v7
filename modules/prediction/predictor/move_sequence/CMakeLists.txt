cmake_minimum_required(VERSION 3.16)

project(modules_prediction_predictor_move_sequence)
message("${Green} [info] modules_prediction_predictor_move_sequence cmakelist ${ColourReset}")

add_library(modules_prediction_predictor_move_sequence_move_sequence_predictor  SHARED
  move_sequence_predictor.cc
)
set_target_properties(modules_prediction_predictor_move_sequence_move_sequence_predictor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_move_sequence_move_sequence_predictor
  modules::prediction::common::prediction_util
  modules::prediction::predictor::sequence::sequence_predictor
)
add_library(modules::prediction::predictor::move_sequence::move_sequence_predictor  ALIAS   modules_prediction_predictor_move_sequence_move_sequence_predictor)

