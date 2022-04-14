cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_detector_point_pillars_detection)
message("${Green} [info] modules_perception_lidar_lib_detector_point_pillars_detection cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_detector_point_pillars_detection_params  SHARED
  ${virtual_cc}
  params.h
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_params  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::point_pillars_detection::params  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_params)

add_library(modules_perception_lidar_lib_detector_point_pillars_detection_point_pillars  SHARED
  point_pillars.cc
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_point_pillars  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_point_pillars_detection_point_pillars
  modules::perception::lidar::lib::detector::point_pillars_detection::anchor_mask_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::common
  modules::perception::lidar::lib::detector::point_pillars_detection::nms_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::params
  modules::perception::lidar::lib::detector::point_pillars_detection::pfe_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::postprocess_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::preprocess_points
  modules::perception::lidar::lib::detector::point_pillars_detection::scatter_cuda
  cyber::common::common
  modules::perception::common::perception_gflags
  ${libtorch}
  ${cuda}
  ${tensorrt}
  
)
add_library(modules::perception::lidar::lib::detector::point_pillars_detection::point_pillars  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_point_pillars)

add_library(modules_perception_lidar_lib_detector_point_pillars_detection_point_pillars_detection  SHARED
  point_pillars_detection.cc
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_point_pillars_detection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_point_pillars_detection_point_pillars_detection
  modules::perception::lidar::lib::detector::point_pillars_detection::point_pillars
  cyber::common::common
  modules::perception::base::base
  modules::perception::lib::thread::thread
  modules::perception::lidar::common::common
  modules::perception::lidar::lib::interface::base_lidar_detector
  ${eigen}
  ${pcl}
  
)
add_library(modules::perception::lidar::lib::detector::point_pillars_detection::point_pillars_detection  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_point_pillars_detection)

add_library(modules_perception_lidar_lib_detector_point_pillars_detection_preprocess_points  SHARED
  preprocess_points.cc
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_preprocess_points  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_point_pillars_detection_preprocess_points
  modules::perception::lidar::lib::detector::point_pillars_detection::common
  modules::perception::lidar::lib::detector::point_pillars_detection::preprocess_points_cuda
)
add_library(modules::perception::lidar::lib::detector::point_pillars_detection::preprocess_points  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_preprocess_points)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_detector_point_pillars_detection_common  SHARED
  ${virtual_cc}
  common.h
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_common  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::point_pillars_detection::common  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_common)

cuda_add_library(modules_perception_lidar_lib_detector_point_pillars_detection_anchor_mask_cuda
  anchor_mask_cuda.cu
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_anchor_mask_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_point_pillars_detection_anchor_mask_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::common
  ${cuda}
)
add_library(modules::perception::lidar::lib::detector::point_pillars_detection::anchor_mask_cuda  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_anchor_mask_cuda)

cuda_add_library(modules_perception_lidar_lib_detector_point_pillars_detection_nms_cuda
  nms_cuda.cu
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_nms_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_point_pillars_detection_nms_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::common
  ${cuda}
)
add_library(modules::perception::lidar::lib::detector::point_pillars_detection::nms_cuda  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_nms_cuda)

cuda_add_library(modules_perception_lidar_lib_detector_point_pillars_detection_pfe_cuda
  pfe_cuda.cu
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_pfe_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_point_pillars_detection_pfe_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::common
  ${cuda}
)
add_library(modules::perception::lidar::lib::detector::point_pillars_detection::pfe_cuda  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_pfe_cuda)

cuda_add_library(modules_perception_lidar_lib_detector_point_pillars_detection_postprocess_cuda
  postprocess_cuda.cu
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_postprocess_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_point_pillars_detection_postprocess_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::common
  modules::perception::lidar::lib::detector::point_pillars_detection::nms_cuda
  ${cuda}
)
add_library(modules::perception::lidar::lib::detector::point_pillars_detection::postprocess_cuda  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_postprocess_cuda)

cuda_add_library(modules_perception_lidar_lib_detector_point_pillars_detection_preprocess_points_cuda
  preprocess_points_cuda.cu
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_preprocess_points_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_point_pillars_detection_preprocess_points_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::common
  ${cuda}
)
add_library(modules::perception::lidar::lib::detector::point_pillars_detection::preprocess_points_cuda  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_preprocess_points_cuda)

cuda_add_library(modules_perception_lidar_lib_detector_point_pillars_detection_scatter_cuda
  scatter_cuda.cu
)
set_target_properties(modules_perception_lidar_lib_detector_point_pillars_detection_scatter_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_point_pillars_detection_scatter_cuda
  modules::perception::lidar::lib::detector::point_pillars_detection::common
  ${cuda}
)
add_library(modules::perception::lidar::lib::detector::point_pillars_detection::scatter_cuda  ALIAS   modules_perception_lidar_lib_detector_point_pillars_detection_scatter_cuda)

