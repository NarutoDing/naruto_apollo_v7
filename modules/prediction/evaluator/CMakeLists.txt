cmake_minimum_required(VERSION 3.16)

project(modules_prediction_evaluator)
message("${Green} [info] modules_prediction_evaluator cmakelist ${ColourReset}")

add_library(modules_prediction_evaluator_evaluator_manager  SHARED
  evaluator_manager.cc
)
set_target_properties(modules_prediction_evaluator_evaluator_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_evaluator_manager
  modules::common::configs::vehicle_config_helper
  modules::prediction::common::feature_output
  modules::prediction::common::prediction_gflags
  modules::prediction::common::prediction_thread_pool
  modules::prediction::common::semantic_map
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::cyclist::cyclist_keep_lane_evaluator
  modules::prediction::evaluator::vehicle::cost_evaluator
  modules::prediction::evaluator::vehicle::cruise_mlp_evaluator
  modules::prediction::evaluator::vehicle::junction_map_evaluator
  modules::prediction::evaluator::vehicle::junction_mlp_evaluator
  modules::prediction::evaluator::vehicle::lane_aggregating_evaluator
  modules::prediction::evaluator::vehicle::lane_scanning_evaluator
  modules::prediction::evaluator::vehicle::mlp_evaluator
  modules::prediction::evaluator::vehicle::semantic_lstm_evaluator
  modules::prediction::evaluator::vehicle::jointly_prediction_planning_evaluator
  modules::prediction::evaluator::vehicle::vectornet_evaluator
  modules::prediction::proto::prediction_conf_cc_proto
  modules::prediction::pipeline::vector_net
  ${libtorch}
)
add_library(modules::prediction::evaluator::evaluator_manager  ALIAS   modules_prediction_evaluator_evaluator_manager)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_prediction_evaluator_evaluator  SHARED
  ${virtual_cc}
  evaluator.h
)
set_target_properties(modules_prediction_evaluator_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_evaluator
  modules::prediction::container::obstacles::obstacle
  modules::prediction::container::adc_trajectory::adc_trajectory_container
)
add_library(modules::prediction::evaluator::evaluator  ALIAS   modules_prediction_evaluator_evaluator)

