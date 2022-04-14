cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_tracker_common)
message("${Green} [info] modules_perception_lidar_lib_tracker_common cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_tracker_common_tracked_object  SHARED
  tracked_object.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_common_tracked_object  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_common_tracked_object
  cyber::cyber
  modules::perception::base::object
  modules::perception::base::object_pool_types
  modules::perception::base::point_cloud
  modules::perception::common::point_cloud_processing::point_cloud_processing
  modules::perception::lidar::common::feature_descriptor
)
add_library(modules::perception::lidar::lib::tracker::common::tracked_object  ALIAS   modules_perception_lidar_lib_tracker_common_tracked_object)

add_library(modules_perception_lidar_lib_tracker_common_track_data  SHARED
  track_data.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_common_track_data  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_common_track_data
  modules::perception::lidar::lib::tracker::common::tracked_object
  cyber::cyber
  modules::perception::base::object_pool
)
add_library(modules::perception::lidar::lib::tracker::common::track_data  ALIAS   modules_perception_lidar_lib_tracker_common_track_data)

add_library(modules_perception_lidar_lib_tracker_common_mlf_track_data_with_track_pool_types  SHARED
  mlf_track_data.cc
  track_pool_types.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_common_mlf_track_data_with_track_pool_types  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_common_mlf_track_data_with_track_pool_types
  modules::perception::lidar::lib::tracker::common::track_data
  cyber::cyber
  modules::perception::base::object_pool
  ${eigen}
)
add_library(modules::perception::lidar::lib::tracker::common::mlf_track_data_with_track_pool_types  ALIAS   modules_perception_lidar_lib_tracker_common_mlf_track_data_with_track_pool_types)

