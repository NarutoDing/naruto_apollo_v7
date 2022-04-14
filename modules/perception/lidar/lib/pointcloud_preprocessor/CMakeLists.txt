cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_pointcloud_preprocessor)
message("${Green} [info] modules_perception_lidar_lib_pointcloud_preprocessor cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_pointcloud_preprocessor_pointcloud_preprocessor  SHARED
  pointcloud_preprocessor.cc
)
set_target_properties(modules_perception_lidar_lib_pointcloud_preprocessor_pointcloud_preprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_pointcloud_preprocessor_pointcloud_preprocessor
  cyber::cyber
  modules::common::configs::vehicle_config_helper
  modules::common::util::util
  modules::drivers::proto::pointcloud_cc_proto
  modules::perception::base::base
  modules::perception::lib::registerer::registerer
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::common::common
  modules::perception::lidar::lib::interface::base_pointcloud_preprocessor
  modules::perception::lidar::lib::pointcloud_preprocessor::proto::pointcloud_preprocessor_config_cc_proto
  ${eigen}
  
)
add_library(modules::perception::lidar::lib::pointcloud_preprocessor::pointcloud_preprocessor  ALIAS   modules_perception_lidar_lib_pointcloud_preprocessor_pointcloud_preprocessor)

