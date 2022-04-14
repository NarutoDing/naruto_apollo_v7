cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_test)
message("${Green} [info] modules_perception_camera_test cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_test_camera_common_io_util  SHARED
  ${virtual_cc}
  camera_common_io_util.h
)
set_target_properties(modules_perception_camera_test_camera_common_io_util  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::camera::test::camera_common_io_util  ALIAS   modules_perception_camera_test_camera_common_io_util)

add_library(modules_perception_camera_test_camera_common_undistortion  SHARED
  camera_common_undistortion.cc
)
set_target_properties(modules_perception_camera_test_camera_common_undistortion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_test_camera_common_undistortion
  modules::perception::base::base
  third_party::boost
  ${yaml}
  ${opencv}
)
add_library(modules::perception::camera::test::camera_common_undistortion  ALIAS   modules_perception_camera_test_camera_common_undistortion)

add_library(modules_perception_camera_test_camera_lib_calibrator_laneline_app_util  SHARED
  camera_lib_calibrator_laneline_app_util.cc
)
set_target_properties(modules_perception_camera_test_camera_lib_calibrator_laneline_app_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_test_camera_lib_calibrator_laneline_app_util
  modules::perception::common::i_lib::core::core
  modules::perception::common::i_lib::geometry::i_plane
  third_party::boost
  ${opencv}
)
add_library(modules::perception::camera::test::camera_lib_calibrator_laneline_app_util  ALIAS   modules_perception_camera_test_camera_lib_calibrator_laneline_app_util)

add_library(modules_perception_camera_test_camera_lib_calibrator_laneline_lane_calibrator_util  SHARED
  camera_lib_calibrator_laneline_lane_calibrator_util.cc
)
set_target_properties(modules_perception_camera_test_camera_lib_calibrator_laneline_lane_calibrator_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_test_camera_lib_calibrator_laneline_lane_calibrator_util
  modules::perception::common::i_lib::core::core
  modules::perception::common::i_lib::geometry::i_plane
  ${eigen}
  ${opencv}
)
add_library(modules::perception::camera::test::camera_lib_calibrator_laneline_lane_calibrator_util  ALIAS   modules_perception_camera_test_camera_lib_calibrator_laneline_lane_calibrator_util)

add_library(modules_perception_camera_test_camera_lib_calibrator_laneline_lane_io  SHARED
  camera_lib_calibrator_laneline_lane_io.cc
)
set_target_properties(modules_perception_camera_test_camera_lib_calibrator_laneline_lane_io  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_test_camera_lib_calibrator_laneline_lane_io
  modules::perception::camera::test::camera_lib_calibrator_laneline_app_util
  modules::perception::camera::lib::calibrator::laneline::lane_based_calibrator
  modules::perception::common::i_lib::core::core
  ${absl}
  ${eigen}
)
add_library(modules::perception::camera::test::camera_lib_calibrator_laneline_lane_io  ALIAS   modules_perception_camera_test_camera_lib_calibrator_laneline_lane_io)

