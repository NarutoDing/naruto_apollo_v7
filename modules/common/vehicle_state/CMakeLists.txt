cmake_minimum_required(VERSION 3.16)

project(modules_common_vehicle_state)
message("${Green} [info] modules_common_vehicle_state cmakelist ${ColourReset}")

add_library(modules_common_vehicle_state_vehicle_state_provider  SHARED
  vehicle_state_provider.cc
)
set_target_properties(modules_common_vehicle_state_vehicle_state_provider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_vehicle_state_vehicle_state_provider
  cyber::common::log
  modules::common::configs::config_gflags
  modules::common::math::geometry
  modules::common::math::quaternion
  modules::common::status::status
  modules::common::vehicle_state::proto::vehicle_state_cc_proto
  modules::localization::common::localization_common
  ${eigen}
)
add_library(modules::common::vehicle_state::vehicle_state_provider  ALIAS   modules_common_vehicle_state_vehicle_state_provider)

