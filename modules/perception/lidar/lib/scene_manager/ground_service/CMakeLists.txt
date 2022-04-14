cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_scene_manager_ground_service)
message("${Green} [info] modules_perception_lidar_lib_scene_manager_ground_service cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_scene_manager_ground_service_ground_struct  SHARED
  ${virtual_cc}
  ground_struct.h
)
set_target_properties(modules_perception_lidar_lib_scene_manager_ground_service_ground_struct  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_scene_manager_ground_service_ground_struct
  ${eigen}
)
add_library(modules::perception::lidar::lib::scene_manager::ground_service::ground_struct  ALIAS   modules_perception_lidar_lib_scene_manager_ground_service_ground_struct)

add_library(modules_perception_lidar_lib_scene_manager_ground_service_ground_service  SHARED
  ground_service.cc
)
set_target_properties(modules_perception_lidar_lib_scene_manager_ground_service_ground_service  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_scene_manager_ground_service_ground_service
  modules::perception::lidar::lib::scene_manager::ground_service::ground_struct
  modules::perception::common::i_lib::i_lib
  modules::perception::lidar::lib::scene_manager::scene_manager
  modules::perception::lidar::lib::scene_manager::ground_service::proto::ground_service_config_cc_proto
)
add_library(modules::perception::lidar::lib::scene_manager::ground_service::ground_service  ALIAS   modules_perception_lidar_lib_scene_manager_ground_service_ground_service)

