cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_object_filter_bank)
message("${Green} [info] modules_perception_lidar_lib_object_filter_bank cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_object_filter_bank_object_filter_bank  SHARED
  object_filter_bank.cc
)
set_target_properties(modules_perception_lidar_lib_object_filter_bank_object_filter_bank  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_object_filter_bank_object_filter_bank
  cyber::cyber
  modules::common::util::util
  modules::perception::base::base
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::interface::interface
  modules::perception::lidar::lib::object_filter_bank::proto::filter_bank_config_cc_proto
  modules::perception::proto::perception_config_schema_cc_proto
  ${eigen}
)
add_library(modules::perception::lidar::lib::object_filter_bank::object_filter_bank  ALIAS   modules_perception_lidar_lib_object_filter_bank_object_filter_bank)

