cmake_minimum_required(VERSION 3.16)

project(modules_prediction_predictor_single_lane)
message("${Green} [info] modules_prediction_predictor_single_lane cmakelist ${ColourReset}")

add_library(modules_prediction_predictor_single_lane_single_lane_predictor  SHARED
  single_lane_predictor.cc
)
set_target_properties(modules_prediction_predictor_single_lane_single_lane_predictor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_single_lane_single_lane_predictor
  modules::prediction::predictor::sequence::sequence_predictor
)
add_library(modules::prediction::predictor::single_lane::single_lane_predictor  ALIAS   modules_prediction_predictor_single_lane_single_lane_predictor)

