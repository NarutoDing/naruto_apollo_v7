cmake_minimum_required(VERSION 3.16)

project(modules_common_vehicle_model)
message("${Green} [info] modules_common_vehicle_model cmakelist ${ColourReset}")

add_library(modules_common_vehicle_model_vehicle_model  SHARED
  vehicle_model.cc
)
set_target_properties(modules_common_vehicle_model_vehicle_model  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_vehicle_model_vehicle_model
  cyber::common::file
  modules::common::configs::config_gflags
  modules::common::configs::vehicle_config_helper
  modules::common::vehicle_model::proto::vehicle_model_config_cc_proto
  modules::common::vehicle_state::proto::vehicle_state_cc_proto
)
add_library(modules::common::vehicle_model::vehicle_model  ALIAS   modules_common_vehicle_model_vehicle_model)

