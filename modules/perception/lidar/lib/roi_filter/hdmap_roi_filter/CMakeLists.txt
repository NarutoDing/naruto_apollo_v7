cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter)
message("${Green} [info] modules_perception_lidar_lib_roi_filter_hdmap_roi_filter cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_bitmap2d  SHARED
  bitmap2d.cc
)
set_target_properties(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_bitmap2d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_bitmap2d
  cyber::cyber
  modules::perception::lidar::common::lidar_log
  ${boost}
  ${eigen}
)
add_library(modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::bitmap2d  ALIAS   modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_bitmap2d)

add_library(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_hdmap_roi_filter  SHARED
  hdmap_roi_filter.cc
)
set_target_properties(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_hdmap_roi_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_hdmap_roi_filter
  modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::bitmap2d
  modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::polygon_mask
  modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::polygon_scan_cvter
  cyber::cyber
  modules::perception::base::point_cloud
  modules::perception::lidar::common::lidar_point_label
  modules::perception::lidar::lib::interface::base_object_filter
  modules::perception::lidar::lib::interface::base_roi_filter
  modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::proto::hdmap_roi_filter_cc_proto
  modules::perception::lidar::lib::scene_manager::scene_manager
  modules::perception::lidar::lib::scene_manager::roi_service::roi_service
  ${eigen}
  
)
add_library(modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::hdmap_roi_filter  ALIAS   modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_hdmap_roi_filter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_polygon_mask  SHARED
  ${virtual_cc}
  polygon_mask.h
)
set_target_properties(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_polygon_mask  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_polygon_mask
  modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::bitmap2d
  modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::polygon_scan_cvter
  modules::perception::lidar::common::lidar_log
  ${eigen}
)
add_library(modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::polygon_mask  ALIAS   modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_polygon_mask)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_polygon_scan_cvter  SHARED
  ${virtual_cc}
  polygon_scan_cvter.h
)
set_target_properties(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_polygon_scan_cvter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_polygon_scan_cvter
  modules::perception::lidar::common::lidar_log
  ${eigen}
)
add_library(modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::polygon_scan_cvter  ALIAS   modules_perception_lidar_lib_roi_filter_hdmap_roi_filter_polygon_scan_cvter)

