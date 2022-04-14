cmake_minimum_required(VERSION 3.16)

project(modules_planning_tuning)
message("${Green} [info] modules_planning_tuning cmakelist ${ColourReset}")

add_library(modules_planning_tuning_autotuning_raw_feature_generator  SHARED
  autotuning_raw_feature_generator.cc
)
set_target_properties(modules_planning_tuning_autotuning_raw_feature_generator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tuning_autotuning_raw_feature_generator
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::reference_line_info
  modules::planning::common::speed_limit
  modules::planning::proto::auto_tuning_raw_feature_cc_proto
)
add_library(modules::planning::tuning::autotuning_raw_feature_generator  ALIAS   modules_planning_tuning_autotuning_raw_feature_generator)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_tuning_autotuning_feature_builder  SHARED
  ${virtual_cc}
  autotuning_feature_builder.h
)
set_target_properties(modules_planning_tuning_autotuning_feature_builder  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tuning_autotuning_feature_builder
  modules::common::status::status
  modules::planning::proto::auto_tuning_model_input_cc_proto
  modules::planning::proto::auto_tuning_raw_feature_cc_proto
)
add_library(modules::planning::tuning::autotuning_feature_builder  ALIAS   modules_planning_tuning_autotuning_feature_builder)

add_library(modules_planning_tuning_autotuning_mlp_net_model  SHARED
  autotuning_mlp_net_model.cc
)
set_target_properties(modules_planning_tuning_autotuning_mlp_net_model  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tuning_autotuning_mlp_net_model
  cyber::common::macros
  modules::prediction::network::net_model
)
add_library(modules::planning::tuning::autotuning_mlp_net_model  ALIAS   modules_planning_tuning_autotuning_mlp_net_model)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_tuning_autotuning_base_model  SHARED
  ${virtual_cc}
  autotuning_base_model.h
)
set_target_properties(modules_planning_tuning_autotuning_base_model  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tuning_autotuning_base_model
  modules::planning::tuning::autotuning_feature_builder
  modules::planning::tuning::autotuning_mlp_net_model
  modules::common::status::status
  modules::planning::proto::auto_tuning_model_input_cc_proto
)
add_library(modules::planning::tuning::autotuning_base_model  ALIAS   modules_planning_tuning_autotuning_base_model)

