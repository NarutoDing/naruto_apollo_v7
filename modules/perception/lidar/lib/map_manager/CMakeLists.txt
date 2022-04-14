cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_map_manager)
message("${Green} [info] modules_perception_lidar_lib_map_manager cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_map_manager_map_manager  SHARED
  map_manager.cc
)
set_target_properties(modules_perception_lidar_lib_map_manager_map_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_map_manager_map_manager
  cyber::cyber
  modules::common::math::math
  modules::map::hdmap::hdmap
  modules::perception::base::base_type
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::common::lidar_frame
  modules::perception::map::hdmap::hdmap_input
  modules::perception::proto::map_manager_config_cc_proto
  
)
add_library(modules::perception::lidar::lib::map_manager::map_manager  ALIAS   modules_perception_lidar_lib_map_manager_map_manager)

