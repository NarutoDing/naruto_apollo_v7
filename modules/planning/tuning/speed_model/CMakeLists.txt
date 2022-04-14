cmake_minimum_required(VERSION 3.16)

project(modules_planning_tuning_speed_model)
message("${Green} [info] modules_planning_tuning_speed_model cmakelist ${ColourReset}")

add_library(modules_planning_tuning_speed_model_autotuning_speed_feature_builder  SHARED
  autotuning_speed_feature_builder.cc
)
set_target_properties(modules_planning_tuning_speed_model_autotuning_speed_feature_builder  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tuning_speed_model_autotuning_speed_feature_builder
  cyber::common::log
  modules::common::proto::error_code_cc_proto
  modules::planning::tuning::autotuning_feature_builder
)
add_library(modules::planning::tuning::speed_model::autotuning_speed_feature_builder  ALIAS   modules_planning_tuning_speed_model_autotuning_speed_feature_builder)

add_library(modules_planning_tuning_speed_model_autotuning_speed_mlp_model  SHARED
  autotuning_speed_mlp_model.cc
)
set_target_properties(modules_planning_tuning_speed_model_autotuning_speed_mlp_model  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tuning_speed_model_autotuning_speed_mlp_model
  modules::planning::tuning::speed_model::autotuning_speed_feature_builder
  modules::planning::tuning::autotuning_base_model
)
add_library(modules::planning::tuning::speed_model::autotuning_speed_mlp_model  ALIAS   modules_planning_tuning_speed_model_autotuning_speed_mlp_model)

