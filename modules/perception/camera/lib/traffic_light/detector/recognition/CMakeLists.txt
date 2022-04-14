cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_traffic_light_detector_recognition)
message("${Green} [info] modules_perception_camera_lib_traffic_light_detector_recognition cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_traffic_light_detector_recognition_classify  SHARED
  classify.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_detector_recognition_classify  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_traffic_light_detector_recognition_classify
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::traffic_light::detector::recognition::proto::recognition_cc_proto
  modules::perception::inference::inference_factory
  modules::perception::inference::inference_lib
  modules::perception::inference::utils::inference_resize_lib
  modules::perception::inference::utils::inference_util_lib
)
add_library(modules::perception::camera::lib::traffic_light::detector::recognition::classify  ALIAS   modules_perception_camera_lib_traffic_light_detector_recognition_classify)

add_library(modules_perception_camera_lib_traffic_light_detector_recognition_recognition  SHARED
  recognition.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_detector_recognition_recognition  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_traffic_light_detector_recognition_recognition
  modules::perception::camera::lib::traffic_light::detector::recognition::classify
  cyber::common::file
  modules::perception::camera::lib::interface::interface
  modules::perception::inference::inference_lib
  
)
add_library(modules::perception::camera::lib::traffic_light::detector::recognition::recognition  ALIAS   modules_perception_camera_lib_traffic_light_detector_recognition_recognition)

