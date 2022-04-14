cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_scene_manager)
message("${Green} [info] modules_perception_lidar_lib_scene_manager cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_scene_manager_scene_manager  SHARED
  scene_manager.cc
)
set_target_properties(modules_perception_lidar_lib_scene_manager_scene_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_scene_manager_scene_manager
  modules::perception::lidar::lib::scene_manager::scene_service
  modules::common::util::util
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::thread::thread
  modules::perception::lidar::lib::scene_manager::proto::scene_manager_config_cc_proto
  modules::perception::proto::perception_config_schema_cc_proto
)
add_library(modules::perception::lidar::lib::scene_manager::scene_manager  ALIAS   modules_perception_lidar_lib_scene_manager_scene_manager)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_scene_manager_scene_service  SHARED
  ${virtual_cc}
  scene_service.h
)
set_target_properties(modules_perception_lidar_lib_scene_manager_scene_service  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_scene_manager_scene_service
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::lidar::lib::scene_manager::scene_service  ALIAS   modules_perception_lidar_lib_scene_manager_scene_service)

