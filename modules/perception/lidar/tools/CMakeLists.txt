cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_tools)
message("${Green} [info] modules_perception_lidar_tools cmakelist ${ColourReset}")

add_executable(offline_lidar_obstacle_perception
  offline_lidar_obstacle_perception.cc
)
target_link_libraries(offline_lidar_obstacle_perception
  cyber::cyber
  modules::perception::base::base
  modules::perception::common::perception_gflags
  modules::perception::common::io::io_util
  modules::perception::common::point_cloud_processing::point_cloud_processing
  modules::perception::common::sensor_manager::sensor_manager
  modules::perception::lidar::app::app
  modules::perception::lidar::lib::classifier::fused_classifier::fused_classifier
  modules::perception::lidar::lib::classifier::fused_classifier::ccrf_type_fusion
  modules::perception::lidar::lib::detection::lidar_point_pillars::point_pillars
  modules::perception::lidar::lib::ground_detector::spatio_temporal_ground_detector::spatio_temporal_ground_detector
  modules::perception::lidar::lib::object_builder::object_builder
  modules::perception::lidar::lib::object_filter_bank::roi_boundary_filter::roi_boundary_filter
  modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::hdmap_roi_filter
  modules::perception::lidar::lib::scene_manager::ground_service::ground_service
  modules::perception::lidar::lib::scene_manager::roi_service::roi_service
  modules::perception::lidar::lib::segmentation::cnnseg::cnn_segmentation
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_engine
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_track_object_matcher
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_tracker
  modules::perception::proto::perception_config_schema_cc_proto
  ${cblas}
  ${eigen}
  ${pcl}
)
