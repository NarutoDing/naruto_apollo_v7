cmake_minimum_required(VERSION 3.16)

project(modules_prediction_predictor_extrapolation)
message("${Green} [info] modules_prediction_predictor_extrapolation cmakelist ${ColourReset}")

add_library(modules_prediction_predictor_extrapolation_extrapolation_predictor  SHARED
  extrapolation_predictor.cc
)
set_target_properties(modules_prediction_predictor_extrapolation_extrapolation_predictor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_extrapolation_extrapolation_predictor
  modules::common::math::geometry
  modules::prediction::common::prediction_gflags
  modules::prediction::common::prediction_map
  modules::prediction::common::prediction_util
  modules::prediction::container::obstacles::obstacle_clusters
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::predictor::sequence::sequence_predictor
  modules::prediction::proto::lane_graph_cc_proto
)
add_library(modules::prediction::predictor::extrapolation::extrapolation_predictor  ALIAS   modules_prediction_predictor_extrapolation_extrapolation_predictor)

