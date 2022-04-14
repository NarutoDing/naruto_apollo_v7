cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_lib_roi_filter_hdmap_radar_roi_filter)
message("${Green} [info] modules_perception_radar_lib_roi_filter_hdmap_radar_roi_filter cmakelist ${ColourReset}")

add_library(modules_perception_radar_lib_roi_filter_hdmap_radar_roi_filter_hdmap_radar_roi_filter  SHARED
  hdmap_radar_roi_filter.cc
)
set_target_properties(modules_perception_radar_lib_roi_filter_hdmap_radar_roi_filter_hdmap_radar_roi_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_roi_filter_hdmap_radar_roi_filter_hdmap_radar_roi_filter
  modules::perception::base::base
  modules::perception::common::geometry::roi_filter
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::registerer::registerer
  modules::perception::proto::perception_config_schema_cc_proto
  modules::perception::radar::lib::interface::base_roi_filter
  ${eigen}
  
)
add_library(modules::perception::radar::lib::roi_filter::hdmap_radar_roi_filter::hdmap_radar_roi_filter  ALIAS   modules_perception_radar_lib_roi_filter_hdmap_radar_roi_filter_hdmap_radar_roi_filter)

