cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_lib_tracker_common)
message("${Green} [info] modules_perception_radar_lib_tracker_common cmakelist ${ColourReset}")

add_library(modules_perception_radar_lib_tracker_common_radar_track_manager  SHARED
  radar_track_manager.cc
)
set_target_properties(modules_perception_radar_lib_tracker_common_radar_track_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_tracker_common_radar_track_manager
  modules::perception::radar::lib::tracker::common::radar_track
  ${eigen}
  
)
add_library(modules::perception::radar::lib::tracker::common::radar_track_manager  ALIAS   modules_perception_radar_lib_tracker_common_radar_track_manager)

add_library(modules_perception_radar_lib_tracker_common_radar_track  SHARED
  radar_track.cc
)
set_target_properties(modules_perception_radar_lib_tracker_common_radar_track  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_tracker_common_radar_track
  modules::perception::base::base
  modules::perception::radar::common::types
  modules::perception::radar::lib::interface::base_filter
  modules::perception::radar::lib::tracker::filter::adaptive_kalman_filter
  ${eigen}
  
)
add_library(modules::perception::radar::lib::tracker::common::radar_track  ALIAS   modules_perception_radar_lib_tracker_common_radar_track)

