cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_calibrator_laneline)
message("${Green} [info] modules_perception_camera_lib_calibrator_laneline cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_calibrator_laneline_lane_based_calibrator  SHARED
  lane_based_calibrator.cc
)
set_target_properties(modules_perception_camera_lib_calibrator_laneline_lane_based_calibrator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_calibrator_laneline_lane_based_calibrator
  modules::perception::camera::lib::calibrator::laneline::lane_struct_for_calib
  modules::perception::camera::lib::calibrator::common::histogram_estimator
  modules::perception::common::i_lib::core::core
)
add_library(modules::perception::camera::lib::calibrator::laneline::lane_based_calibrator  ALIAS   modules_perception_camera_lib_calibrator_laneline_lane_based_calibrator)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_calibrator_laneline_lane_struct_for_calib  SHARED
  ${virtual_cc}
  lane_struct_for_calib.h
)
set_target_properties(modules_perception_camera_lib_calibrator_laneline_lane_struct_for_calib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_calibrator_laneline_lane_struct_for_calib
  ${eigen}
)
add_library(modules::perception::camera::lib::calibrator::laneline::lane_struct_for_calib  ALIAS   modules_perception_camera_lib_calibrator_laneline_lane_struct_for_calib)

add_library(modules_perception_camera_lib_calibrator_laneline_laneline_calibrator  SHARED
  laneline_calibrator.cc
)
set_target_properties(modules_perception_camera_lib_calibrator_laneline_laneline_calibrator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_calibrator_laneline_laneline_calibrator
  modules::perception::camera::lib::calibrator::laneline::lane_based_calibrator
  modules::perception::camera::lib::interface::interface
  modules::perception::common::i_lib::core::core
  
)
add_library(modules::perception::camera::lib::calibrator::laneline::laneline_calibrator  ALIAS   modules_perception_camera_lib_calibrator_laneline_laneline_calibrator)

