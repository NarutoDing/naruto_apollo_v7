cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_detector_ncut_segmentation_common_graph_felzenszwalb)
message("${Green} [info] modules_perception_lidar_lib_detector_ncut_segmentation_common_graph_felzenszwalb cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_detector_ncut_segmentation_common_graph_felzenszwalb_graph_felzenszwalb  SHARED
  ${virtual_cc}
  convolve.h
  disjoint_set.h
  filter.h
  image.h
  imconv.h
  imutil.h
  misc.h
  segment_graph.h
  segment_image.h
)
set_target_properties(modules_perception_lidar_lib_detector_ncut_segmentation_common_graph_felzenszwalb_graph_felzenszwalb  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::ncut_segmentation::common::graph_felzenszwalb::graph_felzenszwalb  ALIAS   modules_perception_lidar_lib_detector_ncut_segmentation_common_graph_felzenszwalb_graph_felzenszwalb)

