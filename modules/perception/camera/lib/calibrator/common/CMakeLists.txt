cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_calibrator_common)
message("${Green} [info] modules_perception_camera_lib_calibrator_common cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_calibrator_common_histogram_estimator  SHARED
  histogram_estimator.cc
)
set_target_properties(modules_perception_camera_lib_calibrator_common_histogram_estimator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_calibrator_common_histogram_estimator
  cyber::cyber
  modules::perception::common::i_lib::core::core
  ${eigen}
)
add_library(modules::perception::camera::lib::calibrator::common::histogram_estimator  ALIAS   modules_perception_camera_lib_calibrator_common_histogram_estimator)

