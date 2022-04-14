cmake_minimum_required(VERSION 3.16)

project(modules_perception_onboard_component)
message("${Green} [info] modules_perception_onboard_component cmakelist ${ColourReset}")

add_library(modules_perception_onboard_component_perception_component_inner_camera  SHARED
  camera_obstacle_detection_component.cc
  camera_perception_viz_message.cc
  fusion_camera_detection_component.cc
  lane_detection_component.cc
  trafficlights_perception_component.cc
)
set_target_properties(modules_perception_onboard_component_perception_component_inner_camera  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_component_perception_component_inner_camera
  cyber::cyber
  cyber::time::clock
  modules::common::math::math
  modules::common::proto::error_code_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::util::eigen_defs
  modules::common::util::time_util
  modules::drivers::proto::sensor_image_cc_proto
  modules::map::proto::map_cc_proto
  modules::perception::base::base
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::app::cipv_camera
  modules::perception::camera::app::lane_camera_perception
  modules::perception::camera::app::obstacle_camera_perception
  modules::perception::camera::app::obstacle_detection_camera
  modules::perception::camera::app::traffic_light_camera_perception
  modules::perception::camera::lib::traffic_light::preprocessor::tl_preprocessor
  modules::perception::camera::common::common
  modules::perception::camera::lib::motion_service::motion_service_lib
  modules::perception::camera::tools::offline::transform_server
  modules::perception::camera::tools::offline::visualizer
  modules::perception::common::sensor_manager::sensor_manager
  modules::perception::map::hdmap::hdmap_input
  modules::perception::onboard::common_flags::common_flags
  modules::perception::onboard::inner_component_messages::inner_component_messages
  modules::perception::onboard::msg_serializer::msg_serializer
  modules::perception::onboard::proto::fusion_camera_detection_component_cc_proto
  modules::perception::onboard::proto::lane_perception_component_cc_proto
  modules::perception::onboard::proto::trafficlights_perception_component_cc_proto
  modules::perception::onboard::transform_wrapper::transform_wrapper
  modules::perception::proto::perception_camera_cc_proto
  modules::perception::proto::perception_lane_cc_proto
  modules::perception::proto::traffic_light_detection_cc_proto
  modules::transform::proto::transform_cc_proto
  modules::v2x::common::v2x_proxy_gflags
  modules::v2x::proto::v2x_traffic_light_cc_proto
  ${eigen}
  ${opencv}
  
)
add_library(modules::perception::onboard::component::perception_component_inner_camera  ALIAS   modules_perception_onboard_component_perception_component_inner_camera)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_onboard_component_perception_component_inner_lidar  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_onboard_component_perception_component_inner_lidar  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_component_perception_component_inner_lidar
  modules::perception::onboard::component::detection_component
  modules::perception::onboard::component::fusion_component
  modules::perception::onboard::component::radar_detection_component
  modules::perception::onboard::component::recognition_component
  
)
add_library(modules::perception::onboard::component::perception_component_inner_lidar  ALIAS   modules_perception_onboard_component_perception_component_inner_lidar)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_onboard_component_lidar_inner_component_messages  SHARED
  ${virtual_cc}
  lidar_inner_component_messages.h
)
set_target_properties(modules_perception_onboard_component_lidar_inner_component_messages  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_component_lidar_inner_component_messages
  cyber::cyber
  modules::perception::lidar::common::common
  modules::perception::onboard::inner_component_messages::inner_component_messages
)
add_library(modules::perception::onboard::component::lidar_inner_component_messages  ALIAS   modules_perception_onboard_component_lidar_inner_component_messages)

add_library(modules_perception_onboard_component_detection_component  SHARED
  detection_component.cc
)
set_target_properties(modules_perception_onboard_component_detection_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_component_detection_component
  modules::perception::onboard::component::lidar_inner_component_messages
  cyber::time::clock
  modules::common::util::string_util
  modules::perception::common::sensor_manager::sensor_manager
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::common
  modules::perception::lidar::app::lidar_obstacle_detection
  modules::perception::lidar::lib::ground_detector::spatio_temporal_ground_detector::spatio_temporal_ground_detector
  modules::perception::lidar::lib::interface::interface
  modules::perception::lidar::lib::object_builder::object_builder
  modules::perception::lidar::lib::object_filter_bank::roi_boundary_filter::roi_boundary_filter
  modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::hdmap_roi_filter
  modules::perception::lidar::lib::scene_manager::ground_service::ground_service
  modules::perception::lidar::lib::scene_manager::roi_service::roi_service
  modules::perception::lidar::lib::detector::point_pillars_detection::point_pillars_detection
  modules::perception::lidar::lib::detector::cnn_segmentation::cnn_segmentation
  modules::perception::lidar::lib::detector::ncut_segmentation::ncut_segmentation
  modules::perception::onboard::common_flags::common_flags
  modules::perception::onboard::proto::lidar_component_config_cc_proto
  modules::perception::onboard::transform_wrapper::transform_wrapper
  ${eigen}
)
add_library(modules::perception::onboard::component::detection_component  ALIAS   modules_perception_onboard_component_detection_component)

add_library(modules_perception_onboard_component_fusion_component  SHARED
  fusion_component.cc
)
set_target_properties(modules_perception_onboard_component_fusion_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_component_fusion_component
  cyber::time::clock
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::fusion::app::obstacle_multi_sensor_fusion
  modules::perception::fusion::lib::dummy::dummy_algorithms
  modules::perception::fusion::lib::fusion_system::probabilistic_fusion::probabilistic_fusion
  modules::perception::fusion::lib::interface::interface
  modules::perception::fusion::lib::interface::base_multisensor_fusion
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::lib::classifier::fused_classifier::fused_classifier
  modules::perception::lidar::lib::classifier::fused_classifier::ccrf_type_fusion
  modules::perception::map::hdmap::hdmap_input
  modules::perception::onboard::common_flags::common_flags
  modules::perception::onboard::inner_component_messages::inner_component_messages
  modules::perception::onboard::msg_serializer::msg_serializer
  modules::perception::onboard::proto::fusion_component_config_cc_proto
  ${eigen}
  
)
add_library(modules::perception::onboard::component::fusion_component  ALIAS   modules_perception_onboard_component_fusion_component)

add_library(modules_perception_onboard_component_radar_detection_component  SHARED
  radar_detection_component.cc
)
set_target_properties(modules_perception_onboard_component_radar_detection_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_component_radar_detection_component
  cyber::time::clock
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::common::sensor_manager::sensor_manager
  modules::perception::lib::registerer::registerer
  modules::perception::map::hdmap::hdmap_input
  modules::perception::onboard::common_flags::common_flags
  modules::perception::onboard::inner_component_messages::inner_component_messages
  modules::perception::onboard::msg_buffer::msg_buffer
  modules::perception::onboard::proto::radar_component_config_cc_proto
  modules::perception::onboard::transform_wrapper::transform_wrapper
  modules::perception::radar::app::radar_obstacle_perception
  modules::perception::radar::common::radar_util
  modules::perception::radar::lib::detector::conti_ars_detector::conti_ars_detector
  modules::perception::radar::lib::dummy::dummy_algorithms
  modules::perception::radar::lib::interface::base_detector
  modules::perception::radar::lib::interface::base_filter
  modules::perception::radar::lib::interface::base_matcher
  modules::perception::radar::lib::interface::base_preprocessor
  modules::perception::radar::lib::interface::base_radar_obstacle_perception
  modules::perception::radar::lib::interface::base_roi_filter
  modules::perception::radar::lib::interface::base_tracker
  modules::perception::radar::lib::preprocessor::conti_ars_preprocessor::conti_ars_preprocessor
  modules::perception::radar::lib::roi_filter::hdmap_radar_roi_filter::hdmap_radar_roi_filter
  modules::perception::radar::lib::tracker::common::radar_track
  modules::perception::radar::lib::tracker::common::radar_track_manager
  modules::perception::radar::lib::tracker::conti_ars_tracker::conti_ars_tracker
  modules::perception::radar::lib::tracker::filter::adaptive_kalman_filter
  modules::perception::radar::lib::tracker::matcher::hm_matcher
  
)
add_library(modules::perception::onboard::component::radar_detection_component  ALIAS   modules_perception_onboard_component_radar_detection_component)

add_library(modules_perception_onboard_component_recognition_component  SHARED
  recognition_component.cc
)
set_target_properties(modules_perception_onboard_component_recognition_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_component_recognition_component
  modules::perception::onboard::component::lidar_inner_component_messages
  cyber::time::clock
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::common::sensor_manager::sensor_manager
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::app::lidar_obstacle_tracking
  modules::perception::lidar::common::common
  modules::perception::lidar::lib::interface::interface
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_engine
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_track_object_matcher
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_tracker
  modules::perception::onboard::proto::lidar_component_config_cc_proto
  
)
add_library(modules::perception::onboard::component::recognition_component  ALIAS   modules_perception_onboard_component_recognition_component)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libperception_component_camera  SHARED
  ${virtual_cc}
)
set_target_properties(libperception_component_camera  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libperception_component_camera
  modules::perception::onboard::component::perception_component_inner_camera
)
set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libperception_component_lidar  SHARED
  ${virtual_cc}
)
set_target_properties(libperception_component_lidar  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libperception_component_lidar
  modules::perception::onboard::component::perception_component_inner_lidar
)
