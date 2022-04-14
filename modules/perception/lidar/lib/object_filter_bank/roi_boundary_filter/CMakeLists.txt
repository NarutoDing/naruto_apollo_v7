cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_object_filter_bank_roi_boundary_filter)
message("${Green} [info] modules_perception_lidar_lib_object_filter_bank_roi_boundary_filter cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_object_filter_bank_roi_boundary_filter_roi_boundary_filter  SHARED
  roi_boundary_filter.cc
)
set_target_properties(modules_perception_lidar_lib_object_filter_bank_roi_boundary_filter_roi_boundary_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_object_filter_bank_roi_boundary_filter_roi_boundary_filter
  cyber::cyber
  modules::perception::base::point_cloud
  modules::perception::common::geometry::common
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::interface::base_object_filter
  modules::perception::proto::roi_boundary_filter_config_cc_proto
  
  ${eigen}
)
add_library(modules::perception::lidar::lib::object_filter_bank::roi_boundary_filter::roi_boundary_filter  ALIAS   modules_perception_lidar_lib_object_filter_bank_roi_boundary_filter_roi_boundary_filter)

