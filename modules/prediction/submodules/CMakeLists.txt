cmake_minimum_required(VERSION 3.16)

project(modules_prediction_submodules)
message("${Green} [info] modules_prediction_submodules cmakelist ${ColourReset}")

add_library(modules_prediction_submodules_submodule_output  SHARED
  submodule_output.cc
)
set_target_properties(modules_prediction_submodules_submodule_output  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_submodules_submodule_output
  modules::common::util::lru_cache
  modules::perception::proto::perception_obstacle_cc_proto
  modules::prediction::common::prediction_gflags
  modules::prediction::container::obstacles::obstacle
)
add_library(modules::prediction::submodules::submodule_output  ALIAS   modules_prediction_submodules_submodule_output)

add_library(modules_prediction_submodules_evaluator_submodule_lib  SHARED
  evaluator_submodule.cc
)
set_target_properties(modules_prediction_submodules_evaluator_submodule_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_submodules_evaluator_submodule_lib
  cyber::cyber
  cyber::time::clock
  modules::common::adapters::adapter_gflags
  modules::common::adapters::proto::adapter_config_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
  modules::prediction::common::message_process
  modules::prediction::common::prediction_gflags
  modules::prediction::evaluator::evaluator_manager
  
)
add_library(modules::prediction::submodules::evaluator_submodule_lib  ALIAS   modules_prediction_submodules_evaluator_submodule_lib)

add_library(modules_prediction_submodules_predictor_submodule_lib  SHARED
  predictor_submodule.cc
)
set_target_properties(modules_prediction_submodules_predictor_submodule_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_submodules_predictor_submodule_lib
  cyber::cyber
  cyber::time::clock
  modules::common::adapters::adapter_gflags
  modules::common::adapters::proto::adapter_config_cc_proto
  modules::common::util::message_util
  modules::perception::proto::perception_obstacle_cc_proto
  modules::prediction::common::message_process
  modules::prediction::common::prediction_gflags
  modules::prediction::container::adc_trajectory::adc_trajectory_container
  modules::prediction::predictor::predictor_manager
  modules::prediction::proto::prediction_obstacle_cc_proto
  
)
add_library(modules::prediction::submodules::predictor_submodule_lib  ALIAS   modules_prediction_submodules_predictor_submodule_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_prediction_submodules_prediction_lego_lib  SHARED
  ${virtual_cc}
)
set_target_properties(modules_prediction_submodules_prediction_lego_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_submodules_prediction_lego_lib
  modules::prediction::submodules::evaluator_submodule_lib
  modules::prediction::submodules::predictor_submodule_lib
  modules::prediction::prediction_component_lib
)
add_library(modules::prediction::submodules::prediction_lego_lib  ALIAS   modules_prediction_submodules_prediction_lego_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(evaluator_submodule  SHARED
  ${virtual_cc}
)
set_target_properties(evaluator_submodule  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(evaluator_submodule
  modules::prediction::submodules::evaluator_submodule_lib
)
set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(predictor_submodule  SHARED
  ${virtual_cc}
)
set_target_properties(predictor_submodule  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(predictor_submodule
  modules::prediction::submodules::evaluator_submodule_lib
)
set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(prediction_lego  SHARED
  ${virtual_cc}
)
set_target_properties(prediction_lego  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(prediction_lego
  modules::prediction::submodules::prediction_lego_lib
)
