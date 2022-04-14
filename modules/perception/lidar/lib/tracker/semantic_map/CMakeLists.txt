cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_tracker_semantic_map)
message("${Green} [info] modules_perception_lidar_lib_tracker_semantic_map cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_tracker_semantic_map_perception_evaluator_manager  SHARED
  evaluator_manager.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_semantic_map_perception_evaluator_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_semantic_map_perception_evaluator_manager
  modules::common::configs::vehicle_config_helper
  modules::prediction::common::feature_output
  modules::prediction::common::semantic_map
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  modules::prediction::evaluator::vehicle::semantic_lstm_evaluator
)
add_library(modules::perception::lidar::lib::tracker::semantic_map::perception_evaluator_manager  ALIAS   modules_perception_lidar_lib_tracker_semantic_map_perception_evaluator_manager)

