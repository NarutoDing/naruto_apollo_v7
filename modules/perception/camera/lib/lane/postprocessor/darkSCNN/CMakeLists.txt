cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_lane_postprocessor_darkSCNN)
message("${Green} [info] modules_perception_camera_lib_lane_postprocessor_darkSCNN cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_lane_postprocessor_darkSCNN_darkSCNN_lane_postprocessor  SHARED
  darkSCNN_lane_postprocessor.cc
)
set_target_properties(modules_perception_camera_lib_lane_postprocessor_darkSCNN_darkSCNN_lane_postprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_lane_postprocessor_darkSCNN_darkSCNN_lane_postprocessor
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::lane::common::common_functions
  modules::perception::camera::lib::lane::common::proto::darkSCNN_cc_proto
  modules::perception::camera::lib::lane::postprocessor::darkSCNN::proto::darkSCNN_postprocessor_cc_proto
  modules::perception::lib::registerer::registerer
  
)
add_library(modules::perception::camera::lib::lane::postprocessor::darkSCNN::darkSCNN_lane_postprocessor  ALIAS   modules_perception_camera_lib_lane_postprocessor_darkSCNN_darkSCNN_lane_postprocessor)

