cmake_minimum_required(VERSION 3.16)

project(modules_prediction_container_adc_trajectory)
message("${Green} [info] modules_prediction_container_adc_trajectory cmakelist ${ColourReset}")

add_library(modules_prediction_container_adc_trajectory_adc_trajectory_container  SHARED
  adc_trajectory_container.cc
)
set_target_properties(modules_prediction_container_adc_trajectory_adc_trajectory_container  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_container_adc_trajectory_adc_trajectory_container
  modules::planning::proto::planning_cc_proto
  modules::prediction::common::prediction_map
  modules::prediction::container::container
  modules::prediction::proto::lane_graph_cc_proto
)
add_library(modules::prediction::container::adc_trajectory::adc_trajectory_container  ALIAS   modules_prediction_container_adc_trajectory_adc_trajectory_container)

