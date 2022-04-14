cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_detector_ncut_segmentation_common)
message("${Green} [info] modules_perception_lidar_lib_detector_ncut_segmentation_common cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_detector_ncut_segmentation_common_flood_fill  SHARED
  flood_fill.cc
)
set_target_properties(modules_perception_lidar_lib_detector_ncut_segmentation_common_flood_fill  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_ncut_segmentation_common_flood_fill
  cyber::cyber
  modules::perception::base::base
)
add_library(modules::perception::lidar::lib::detector::ncut_segmentation::common::flood_fill  ALIAS   modules_perception_lidar_lib_detector_ncut_segmentation_common_flood_fill)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_detector_ncut_segmentation_common_lr_classifier  SHARED
  ${virtual_cc}
  lr_classifier.h
)
set_target_properties(modules_perception_lidar_lib_detector_ncut_segmentation_common_lr_classifier  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_ncut_segmentation_common_lr_classifier
  cyber::cyber
  modules::perception::base::base
)
add_library(modules::perception::lidar::lib::detector::ncut_segmentation::common::lr_classifier  ALIAS   modules_perception_lidar_lib_detector_ncut_segmentation_common_lr_classifier)

