cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_ground_detector_ground_service_detector)
message("${Green} [info] modules_perception_lidar_lib_ground_detector_ground_service_detector cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_ground_detector_ground_service_detector_ground_service_detector  SHARED
  ground_service_detector.cc
)
set_target_properties(modules_perception_lidar_lib_ground_detector_ground_service_detector_ground_service_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_ground_detector_ground_service_detector_ground_service_detector
  cyber::cyber
  modules::common::util::util
  modules::perception::base::base_type
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::thread::thread
  modules::perception::lidar::common::lidar_frame
  modules::perception::lidar::common::lidar_point_label
  modules::perception::lidar::lib::ground_detector::ground_service_detector::proto::ground_service_detector_config_cc_proto
  modules::perception::lidar::lib::interface::base_ground_detector
  modules::perception::lidar::lib::scene_manager::scene_manager
  modules::perception::lidar::lib::scene_manager::scene_service
  modules::perception::lidar::lib::scene_manager::ground_service::ground_service
  modules::perception::lidar::lib::scene_manager::ground_service::ground_struct
  modules::perception::proto::perception_config_schema_cc_proto
  ${eigen}
)
add_library(modules::perception::lidar::lib::ground_detector::ground_service_detector::ground_service_detector  ALIAS   modules_perception_lidar_lib_ground_detector_ground_service_detector_ground_service_detector)

