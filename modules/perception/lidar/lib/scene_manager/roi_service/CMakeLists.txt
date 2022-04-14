cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_scene_manager_roi_service)
message("${Green} [info] modules_perception_lidar_lib_scene_manager_roi_service cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_scene_manager_roi_service_roi_service  SHARED
  roi_service.cc
)
set_target_properties(modules_perception_lidar_lib_scene_manager_roi_service_roi_service  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_scene_manager_roi_service_roi_service
  modules::common::util::util
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::scene_manager::scene_service
  modules::perception::lidar::lib::scene_manager::roi_service::proto::roi_service_cc_proto
  ${eigen}
)
add_library(modules::perception::lidar::lib::scene_manager::roi_service::roi_service  ALIAS   modules_perception_lidar_lib_scene_manager_roi_service_roi_service)

