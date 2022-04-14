cmake_minimum_required(VERSION 3.16)

project(modules_prediction_predictor)
message("${Green} [info] modules_prediction_predictor cmakelist ${ColourReset}")

add_library(modules_prediction_predictor_predictor_manager  SHARED
  predictor_manager.cc
)
set_target_properties(modules_prediction_predictor_predictor_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_predictor_manager
  modules::prediction::common::feature_output
  modules::prediction::common::prediction_thread_pool
  modules::prediction::predictor::empty::empty_predictor
  modules::prediction::predictor::extrapolation::extrapolation_predictor
  modules::prediction::predictor::free_move::free_move_predictor
  modules::prediction::predictor::interaction::interaction_predictor
  modules::prediction::predictor::junction::junction_predictor
  modules::prediction::predictor::lane_sequence::lane_sequence_predictor
  modules::prediction::predictor::move_sequence::move_sequence_predictor
  modules::prediction::predictor::single_lane::single_lane_predictor
  modules::prediction::proto::prediction_conf_cc_proto
  modules::prediction::scenario::scenario_manager
)
add_library(modules::prediction::predictor::predictor_manager  ALIAS   modules_prediction_predictor_predictor_manager)

add_library(modules_prediction_predictor_predictor  SHARED
  predictor.cc
)
set_target_properties(modules_prediction_predictor_predictor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_predictor_predictor
  modules::prediction::container::adc_trajectory::adc_trajectory_container
  modules::prediction::container::obstacles::obstacle
  modules::prediction::container::obstacles::obstacles_container
)
add_library(modules::prediction::predictor::predictor  ALIAS   modules_prediction_predictor_predictor)

