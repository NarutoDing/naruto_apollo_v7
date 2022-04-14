cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_traffic_light_detector_detection)
message("${Green} [info] modules_perception_camera_lib_traffic_light_detector_detection cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_traffic_light_detector_detection_detection  SHARED
  detection.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_detector_detection_detection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_traffic_light_detector_detection_detection
  modules::perception::camera::lib::traffic_light::detector::detection::cropbox
  modules::perception::camera::lib::traffic_light::detector::detection::select
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::traffic_light::proto::detection_cc_proto
  modules::perception::inference::inference_factory
  modules::perception::inference::inference_lib
  modules::perception::inference::utils::inference_resize_lib
  modules::perception::inference::utils::inference_util_lib
  
)
add_library(modules::perception::camera::lib::traffic_light::detector::detection::detection  ALIAS   modules_perception_camera_lib_traffic_light_detector_detection_detection)

add_library(modules_perception_camera_lib_traffic_light_detector_detection_select  SHARED
  select.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_detector_detection_select  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_traffic_light_detector_detection_select
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::common::graph::hungarian_optimizer
  modules::perception::common::graph::secure_matrix
)
add_library(modules::perception::camera::lib::traffic_light::detector::detection::select  ALIAS   modules_perception_camera_lib_traffic_light_detector_detection_select)

add_library(modules_perception_camera_lib_traffic_light_detector_detection_cropbox  SHARED
  cropbox.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_detector_detection_cropbox  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_traffic_light_detector_detection_cropbox
  modules::perception::base::base
  modules::perception::camera::common::common
)
add_library(modules::perception::camera::lib::traffic_light::detector::detection::cropbox  ALIAS   modules_perception_camera_lib_traffic_light_detector_detection_cropbox)

