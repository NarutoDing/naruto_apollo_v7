cmake_minimum_required(VERSION 3.16)

project(modules_prediction_container)
message("${Green} [info] modules_prediction_container cmakelist ${ColourReset}")

add_library(modules_prediction_container_container_manager  SHARED
  container_manager.cc
)
set_target_properties(modules_prediction_container_container_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_container_container_manager
  modules::common::adapters::proto::adapter_config_cc_proto
  modules::prediction::container::adc_trajectory::adc_trajectory_container
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::container::pose::pose_container
  modules::prediction::container::storytelling::storytelling_container
  
)
add_library(modules::prediction::container::container_manager  ALIAS   modules_prediction_container_container_manager)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_prediction_container_container  SHARED
  ${virtual_cc}
  container.h
)
set_target_properties(modules_prediction_container_container  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::prediction::container::container  ALIAS   modules_prediction_container_container)

