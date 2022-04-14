cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_detector_ncut_segmentation)
message("${Green} [info] modules_perception_lidar_lib_detector_ncut_segmentation cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_detector_ncut_segmentation_ncut  SHARED
  ncut.cc
)
set_target_properties(modules_perception_lidar_lib_detector_ncut_segmentation_ncut  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_ncut_segmentation_ncut
  cyber::cyber
  modules::perception::base::base
  modules::perception::lidar::lib::detector::ncut_segmentation::common::flood_fill
  modules::perception::lidar::lib::detector::ncut_segmentation::common::lr_classifier
  modules::perception::lidar::lib::detector::ncut_segmentation::proto::ncut_config_cc_proto
  modules::perception::lidar::lib::detector::ncut_segmentation::proto::ncut_param_cc_proto
)
add_library(modules::perception::lidar::lib::detector::ncut_segmentation::ncut  ALIAS   modules_perception_lidar_lib_detector_ncut_segmentation_ncut)

add_library(modules_perception_lidar_lib_detector_ncut_segmentation_ncut_segmentation  SHARED
  ncut_segmentation.cc
)
set_target_properties(modules_perception_lidar_lib_detector_ncut_segmentation_ncut_segmentation  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_ncut_segmentation_ncut_segmentation
  modules::perception::lidar::lib::detector::ncut_segmentation::ncut
  cyber::cyber
  modules::perception::base::base
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::thread::thread
  modules::perception::lidar::common::pcl_util
  modules::perception::lidar::lib::interface::interface
  modules::perception::lidar::lib::detector::ncut_segmentation::common::flood_fill
  modules::perception::lidar::lib::detector::ncut_segmentation::common::lr_classifier
  modules::perception::lidar::lib::detector::ncut_segmentation::proto::ncut_param_cc_proto
  modules::perception::lidar::lib::interface::base_lidar_detector
  ${pcl}
  ${vtk}
)
add_library(modules::perception::lidar::lib::detector::ncut_segmentation::ncut_segmentation  ALIAS   modules_perception_lidar_lib_detector_ncut_segmentation_ncut_segmentation)

