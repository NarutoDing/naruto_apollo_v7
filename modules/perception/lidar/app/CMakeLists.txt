cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_app)
message("${Green} [info] modules_perception_lidar_app cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_app_app  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_lidar_app_app  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_app_app
  modules::perception::lidar::app::lidar_obstacle_detection
  modules::perception::lidar::app::lidar_obstacle_tracking
)
add_library(modules::perception::lidar::app::app  ALIAS   modules_perception_lidar_app_app)

add_library(modules_perception_lidar_app_lidar_obstacle_detection  SHARED
  lidar_obstacle_detection.cc
)
set_target_properties(modules_perception_lidar_app_lidar_obstacle_detection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_app_lidar_obstacle_detection
  cyber::cyber
  modules::common::util::perf_util
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::common::lidar_error_code
  modules::perception::lidar::app::proto::lidar_obstacle_detection_config_cc_proto
  modules::perception::lidar::lib::map_manager::map_manager
  modules::perception::lidar::lib::object_builder::object_builder
  modules::perception::lidar::lib::object_filter_bank::object_filter_bank
  modules::perception::lidar::lib::interface::base_lidar_detector
  modules::perception::lidar::lib::interface::base_pointcloud_preprocessor
  modules::perception::lidar::lib::interface::base_lidar_obstacle_detection
  modules::perception::lidar::lib::pointcloud_preprocessor::pointcloud_preprocessor
  modules::perception::lidar::lib::detector::point_pillars_detection::point_pillars_detection
  modules::perception::lidar::lib::detector::cnn_segmentation::cnn_segmentation
  modules::perception::lidar::lib::detector::mask_pillars_detection::mask_pillars_detection
  modules::perception::lidar::lib::detector::ncut_segmentation::ncut_segmentation
  modules::perception::lidar::lib::scene_manager::scene_manager
  ${eigen}
  
)
add_library(modules::perception::lidar::app::lidar_obstacle_detection  ALIAS   modules_perception_lidar_app_lidar_obstacle_detection)

add_library(modules_perception_lidar_app_lidar_obstacle_tracking  SHARED
  lidar_obstacle_tracking.cc
)
set_target_properties(modules_perception_lidar_app_lidar_obstacle_tracking  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_app_lidar_obstacle_tracking
  cyber::cyber
  modules::common::util::util
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::app::proto::lidar_obstacle_tracking_config_cc_proto
  modules::perception::lidar::common::common
  modules::perception::lidar::lib::interface::base_lidar_obstacle_tracking
  modules::perception::lidar::lib::interface::base_classifier
  modules::perception::lidar::lib::interface::base_multi_target_tracker
  modules::perception::lidar::lib::classifier::fused_classifier::fused_classifier
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_engine
  ${eigen}
  
)
add_library(modules::perception::lidar::app::lidar_obstacle_tracking  ALIAS   modules_perception_lidar_app_lidar_obstacle_tracking)

