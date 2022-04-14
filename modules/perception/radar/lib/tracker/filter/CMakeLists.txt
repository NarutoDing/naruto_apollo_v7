cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_lib_tracker_filter)
message("${Green} [info] modules_perception_radar_lib_tracker_filter cmakelist ${ColourReset}")

add_library(modules_perception_radar_lib_tracker_filter_adaptive_kalman_filter  SHARED
  adaptive_kalman_filter.cc
)
set_target_properties(modules_perception_radar_lib_tracker_filter_adaptive_kalman_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_tracker_filter_adaptive_kalman_filter
  modules::perception::base::base
  modules::perception::radar::lib::interface::base_filter
  ${eigen}
  
)
add_library(modules::perception::radar::lib::tracker::filter::adaptive_kalman_filter  ALIAS   modules_perception_radar_lib_tracker_filter_adaptive_kalman_filter)

