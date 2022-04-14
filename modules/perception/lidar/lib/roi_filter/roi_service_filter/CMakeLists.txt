cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_roi_filter_roi_service_filter)
message("${Green} [info] modules_perception_lidar_lib_roi_filter_roi_service_filter cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_roi_filter_roi_service_filter_roi_service_filter  SHARED
  roi_service_filter.cc
)
set_target_properties(modules_perception_lidar_lib_roi_filter_roi_service_filter_roi_service_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_roi_filter_roi_service_filter_roi_service_filter
  cyber::cyber
  modules::perception::base::base_type
  modules::perception::base::blob
  modules::perception::base::box
  modules::perception::base::common
  modules::perception::base::frame
  modules::perception::base::image
  modules::perception::base::impending_collision_edge
  modules::perception::base::object
  modules::perception::base::object_pool_types
  modules::perception::base::point_cloud
  modules::perception::base::syncedmem
  modules::perception::lidar::common::lidar_frame
  modules::perception::lidar::common::lidar_log
  modules::perception::lidar::common::lidar_point_label
  modules::perception::lidar::lib::interface::base_roi_filter
  modules::perception::lidar::lib::scene_manager::scene_manager
  modules::perception::lidar::lib::scene_manager::roi_service::roi_service
  ${eigen}
)
add_library(modules::perception::lidar::lib::roi_filter::roi_service_filter::roi_service_filter  ALIAS   modules_perception_lidar_lib_roi_filter_roi_service_filter_roi_service_filter)

