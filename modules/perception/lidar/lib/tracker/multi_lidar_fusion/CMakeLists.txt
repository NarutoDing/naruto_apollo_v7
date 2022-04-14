cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_tracker_multi_lidar_fusion)
message("${Green} [info] modules_perception_lidar_lib_tracker_multi_lidar_fusion cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_base_filter  SHARED
  ${virtual_cc}
  mlf_base_filter.h
)
set_target_properties(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_base_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_base_filter
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::lib::tracker::common::mlf_track_data_with_track_pool_types
  modules::perception::lidar::lib::tracker::common::tracked_object
)
add_library(modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_base_filter  ALIAS   modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_base_filter)

add_library(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_engine  SHARED
  mlf_engine.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_engine  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_engine
  cyber::common::file
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::interface::base_multi_target_tracker
  modules::perception::lidar::lib::tracker::common::mlf_track_data_with_track_pool_types
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_track_object_matcher
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_tracker
  modules::perception::onboard::msg_serializer::msg_serializer
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::container::pose::pose_container
  
)
add_library(modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_engine  ALIAS   modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_engine)

add_library(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_filter  SHARED
  mlf_motion_filter.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_filter
  cyber::common::file
  modules::perception::common::geometry::basic
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_base_filter
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_motion_measurement
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_motion_refiner
  
)
add_library(modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_motion_filter  ALIAS   modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_filter)

add_library(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_measurement  SHARED
  mlf_motion_measurement.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_measurement  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_measurement
  modules::perception::lidar::lib::tracker::common::mlf_track_data_with_track_pool_types
  modules::perception::lidar::lib::tracker::common::tracked_object
  modules::perception::lidar::lib::tracker::measurement::measurement_collection
  
)
add_library(modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_motion_measurement  ALIAS   modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_measurement)

add_library(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_refiner  SHARED
  mlf_motion_refiner.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_refiner  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_refiner
  cyber::common::file
  modules::perception::common::geometry::basic
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::tracker::common::mlf_track_data_with_track_pool_types
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::proto::multi_lidar_fusion_config_cc_proto
  
)
add_library(modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_motion_refiner  ALIAS   modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_motion_refiner)

add_library(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_shape_filter  SHARED
  mlf_shape_filter.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_shape_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_shape_filter
  cyber::common::file
  modules::perception::common::geometry::convex_hull_2d
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::common::lidar_object_util
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_base_filter
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::proto::multi_lidar_fusion_config_cc_proto
  
)
add_library(modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_shape_filter  ALIAS   modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_shape_filter)

add_library(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_track_object_distance  SHARED
  mlf_track_object_distance.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_track_object_distance  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_track_object_distance
  cyber::common::file
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::tracker::association::distance_collection
  modules::perception::lidar::lib::tracker::common::mlf_track_data_with_track_pool_types
  modules::perception::lidar::lib::tracker::common::tracked_object
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::proto::multi_lidar_fusion_config_cc_proto
  
)
add_library(modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_track_object_distance  ALIAS   modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_track_object_distance)

add_library(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_track_object_matcher  SHARED
  mlf_track_object_matcher.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_track_object_matcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_track_object_matcher
  cyber::common::file
  modules::perception::common::graph::secure_matrix
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::interface::base_bipartite_graph_matcher
  modules::perception::lidar::lib::tracker::association::distance_collection
  modules::perception::lidar::lib::tracker::association::gnn_bipartite_graph_matcher
  modules::perception::lidar::lib::tracker::association::multi_hm_bipartite_graph_matcher
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_track_object_distance
  
)
add_library(modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_track_object_matcher  ALIAS   modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_track_object_matcher)

add_library(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_tracker  SHARED
  mlf_tracker.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_tracker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_tracker
  cyber::common::file
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::tracker::common::mlf_track_data_with_track_pool_types
  modules::perception::lidar::lib::tracker::common::tracked_object
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_base_filter
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_motion_filter
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_motion_measurement
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_motion_refiner
  modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_shape_filter
  
)
add_library(modules::perception::lidar::lib::tracker::multi_lidar_fusion::mlf_tracker  ALIAS   modules_perception_lidar_lib_tracker_multi_lidar_fusion_mlf_tracker)

