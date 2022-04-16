cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_ground_detector_spatio_temporal_ground_detector)
message("${Green} [info] modules_perception_lidar_lib_ground_detector_spatio_temporal_ground_detector cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_ground_detector_spatio_temporal_ground_detector_spatio_temporal_ground_detector  SHARED
  spatio_temporal_ground_detector.cc
)
set_target_properties(modules_perception_lidar_lib_ground_detector_spatio_temporal_ground_detector_spatio_temporal_ground_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_ground_detector_spatio_temporal_ground_detector_spatio_temporal_ground_detector
  cyber::cyber
  modules::perception::base::base
  modules::perception::lib::registerer::registerer
  ${eigen}
  
  #modules::perception::lib::io::protobuf_util #bug
  modules::perception::common::i_lib::i_lib
  modules::perception::common::i_lib::pc::i_ground
  modules::perception::common::i_lib::pc::i_struct_s
  modules::perception::common::i_lib::pc::i_util
  modules::perception::common::point_cloud_processing::point_cloud_processing
  modules::perception::lidar::common::common
  modules::perception::lidar::lib::ground_detector::spatio_temporal_ground_detector::proto::spatio_temporal_ground_detector_config_cc_proto
  modules::perception::lidar::lib::interface::interface
  modules::perception::lidar::lib::scene_manager::scene_manager
  modules::perception::lidar::lib::scene_manager::ground_service::ground_service
  modules::perception::proto::perception_config_schema_cc_proto
)
add_library(modules::perception::lidar::lib::ground_detector::spatio_temporal_ground_detector::spatio_temporal_ground_detector  ALIAS   modules_perception_lidar_lib_ground_detector_spatio_temporal_ground_detector_spatio_temporal_ground_detector)

