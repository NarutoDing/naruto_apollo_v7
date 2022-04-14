cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_dummy)
message("${Green} [info] modules_perception_lidar_lib_dummy cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_dummy_dummy_algorithms  SHARED
  dummy_classifier.cc
  dummy_ground_detector.cc
  dummy_multi_target_tracker.cc
  dummy_object_filter.cc
  dummy_roi_filter.cc
  dummy_segmentation.cc
)
set_target_properties(modules_perception_lidar_lib_dummy_dummy_algorithms  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_dummy_dummy_algorithms
  cyber::cyber
  modules::perception::base::base
  modules::perception::common::point_cloud_processing::point_cloud_processing
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::common
  modules::perception::lidar::lib::interface::interface
  ${eigen}
)
add_library(modules::perception::lidar::lib::dummy::dummy_algorithms  ALIAS   modules_perception_lidar_lib_dummy_dummy_algorithms)

