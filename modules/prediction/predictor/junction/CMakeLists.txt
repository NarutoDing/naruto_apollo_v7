cmake_minimum_required(VERSION 3.16)

project(modules_prediction_predictor_junction)
message("${Green} [info] modules_prediction_predictor_junction cmakelist ${ColourReset}")

add_library(modules_prediction_predictor_junction_junction_predictor  SHARED
  junction_predictor.cc
)
set_target_properties(modules_prediction_predictor_junction_junction_predictor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_junction_junction_predictor
  modules::prediction::common::prediction_util
  modules::prediction::predictor::predictor
)
add_library(modules::prediction::predictor::junction::junction_predictor  ALIAS   modules_prediction_predictor_junction_junction_predictor)

