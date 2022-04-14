cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_calibration_service_online_calibration_service)
message("${Green} [info] modules_perception_camera_lib_calibration_service_online_calibration_service cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_calibration_service_online_calibration_service_online_calibration_service  SHARED
  online_calibration_service.cc
)
set_target_properties(modules_perception_camera_lib_calibration_service_online_calibration_service_online_calibration_service  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_calibration_service_online_calibration_service_online_calibration_service
  modules::perception::camera::lib::interface::interface
  modules::perception::common::i_lib::core::core
  modules::perception::common::i_lib::geometry::i_plane
  
)
add_library(modules::perception::camera::lib::calibration_service::online_calibration_service::online_calibration_service  ALIAS   modules_perception_camera_lib_calibration_service_online_calibration_service_online_calibration_service)

