cmake_minimum_required(VERSION 3.16)

project(modules_prediction_predictor_empty)
message("${Green} [info] modules_prediction_predictor_empty cmakelist ${ColourReset}")

add_library(modules_prediction_predictor_empty_empty_predictor  SHARED
  empty_predictor.cc
)
set_target_properties(modules_prediction_predictor_empty_empty_predictor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_empty_empty_predictor
  modules::prediction::predictor::predictor
)
add_library(modules::prediction::predictor::empty::empty_predictor  ALIAS   modules_prediction_predictor_empty_empty_predictor)

