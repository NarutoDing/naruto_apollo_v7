cmake_minimum_required(VERSION 3.16)

project(modules_common_configs)
message("${Green} [info] modules_common_configs cmakelist ${ColourReset}")

add_library(modules_common_configs_config_gflags  SHARED
  config_gflags.cc
)
set_target_properties(modules_common_configs_config_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_configs_config_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::common::configs::config_gflags  ALIAS   modules_common_configs_config_gflags)

add_library(modules_common_configs_vehicle_config_helper  SHARED
  vehicle_config_helper.cc
)
set_target_properties(modules_common_configs_vehicle_config_helper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_configs_vehicle_config_helper
  modules::common::configs::config_gflags
  cyber::common::file
  cyber::common::macros
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::math::geometry
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::common::configs::vehicle_config_helper  ALIAS   modules_common_configs_vehicle_config_helper)

