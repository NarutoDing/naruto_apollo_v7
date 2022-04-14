cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_detector_mask_pillars_detection)
message("${Green} [info] modules_perception_lidar_lib_detector_mask_pillars_detection cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_detector_mask_pillars_detection_mask_pillars_detection  SHARED
  mask_pillars_detection.cc
)
set_target_properties(modules_perception_lidar_lib_detector_mask_pillars_detection_mask_pillars_detection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_mask_pillars_detection_mask_pillars_detection
  cyber::common::common
  modules::perception::base::base
  modules::perception::lib::thread::thread
  modules::perception::lidar::common::common
  modules::perception::lidar::lib::detector::point_pillars_detection::point_pillars
  modules::perception::lidar::lib::interface::base_lidar_detector
  ${eigen}
  ${pcl}
  
)
add_library(modules::perception::lidar::lib::detector::mask_pillars_detection::mask_pillars_detection  ALIAS   modules_perception_lidar_lib_detector_mask_pillars_detection_mask_pillars_detection)

