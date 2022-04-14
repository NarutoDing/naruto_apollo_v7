cmake_minimum_required(VERSION 3.16)

project(modules_prediction)
message("${Green} [info] modules_prediction cmakelist ${ColourReset}")

add_library(modules_prediction_prediction_component_lib  SHARED
  prediction_component.cc
)
set_target_properties(modules_prediction_prediction_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_prediction_component_lib
  cyber::common::file
  modules::common::adapters::adapter_gflags
  modules::prediction::common::message_process
  modules::prediction::evaluator::evaluator_manager
  modules::prediction::predictor::predictor_manager
  modules::prediction::proto::offline_features_cc_proto
  modules::prediction::scenario::scenario_manager
  modules::prediction::submodules::evaluator_submodule_lib
  modules::prediction::submodules::predictor_submodule_lib
  modules::prediction::submodules::submodule_output
  modules::prediction::util::data_extraction
)
add_library(modules::prediction::prediction_component_lib  ALIAS   modules_prediction_prediction_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libprediction_component  SHARED
  ${virtual_cc}
)
set_target_properties(libprediction_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libprediction_component
  modules::prediction::prediction_component_lib
)
