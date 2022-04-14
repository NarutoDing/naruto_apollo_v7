cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_app)
message("${Green} [info] modules_perception_radar_app cmakelist ${ColourReset}")

add_library(modules_perception_radar_app_radar_obstacle_perception  SHARED
  radar_obstacle_perception.cc
)
set_target_properties(modules_perception_radar_app_radar_obstacle_perception  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_app_radar_obstacle_perception
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::common::geometry::roi_filter
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::registerer::registerer
  modules::perception::radar::common::types
  modules::perception::radar::lib::interface::base_detector
  modules::perception::radar::lib::interface::base_preprocessor
  modules::perception::radar::lib::interface::base_radar_obstacle_perception
  modules::perception::radar::lib::interface::base_roi_filter
  modules::perception::radar::lib::interface::base_tracker
  ${eigen}
  
)
add_library(modules::perception::radar::app::radar_obstacle_perception  ALIAS   modules_perception_radar_app_radar_obstacle_perception)

