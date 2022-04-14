cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_lane_postprocessor_denseline)
message("${Green} [info] modules_perception_camera_lib_lane_postprocessor_denseline cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_lane_postprocessor_denseline_denseline_lane_postprocessor  SHARED
  denseline_lane_postprocessor.cc
)
set_target_properties(modules_perception_camera_lib_lane_postprocessor_denseline_denseline_lane_postprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_lane_postprocessor_denseline_denseline_lane_postprocessor
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::lane::common::common_functions
  modules::perception::camera::lib::lane::common::proto::denseline_cc_proto
  modules::perception::camera::lib::lane::postprocessor::denseline::proto::denseline_postprocessor_cc_proto
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::lane::postprocessor::denseline::denseline_lane_postprocessor  ALIAS   modules_perception_camera_lib_lane_postprocessor_denseline_denseline_lane_postprocessor)

