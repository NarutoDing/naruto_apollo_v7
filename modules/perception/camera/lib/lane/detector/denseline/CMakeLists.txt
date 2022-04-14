cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_lane_detector_denseline)
message("${Green} [info] modules_perception_camera_lib_lane_detector_denseline cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_lane_detector_denseline_denseline_lane_detector  SHARED
  denseline_lane_detector.cc
)
set_target_properties(modules_perception_camera_lib_lane_detector_denseline_denseline_lane_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_lane_detector_denseline_denseline_lane_detector
  cyber::common::file
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::lane::common::proto::denseline_cc_proto
  modules::perception::inference::inference_factory
  modules::perception::inference::tensorrt::rt_net
  modules::perception::inference::utils::inference_resize_lib
  modules::perception::inference::utils::inference_util_lib
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::lane::detector::denseline::denseline_lane_detector  ALIAS   modules_perception_camera_lib_lane_detector_denseline_denseline_lane_detector)

