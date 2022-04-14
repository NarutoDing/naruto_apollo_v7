cmake_minimum_required(VERSION 3.16)

project(modules_prediction_predictor_free_move)
message("${Green} [info] modules_prediction_predictor_free_move cmakelist ${ColourReset}")

add_library(modules_prediction_predictor_free_move_free_move_predictor  SHARED
  free_move_predictor.cc
)
set_target_properties(modules_prediction_predictor_free_move_free_move_predictor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_free_move_free_move_predictor
  modules::prediction::common::prediction_util
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::predictor::predictor
)
add_library(modules::prediction::predictor::free_move::free_move_predictor  ALIAS   modules_prediction_predictor_free_move_free_move_predictor)

