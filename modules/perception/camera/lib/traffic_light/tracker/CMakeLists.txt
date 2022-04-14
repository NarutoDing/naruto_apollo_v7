cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_traffic_light_tracker)
message("${Green} [info] modules_perception_camera_lib_traffic_light_tracker cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_traffic_light_tracker_semantic_decision  SHARED
  semantic_decision.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_tracker_semantic_decision  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_traffic_light_tracker_semantic_decision
  cyber::common::file
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::traffic_light::tracker::proto::semantic_cc_proto
  
)
add_library(modules::perception::camera::lib::traffic_light::tracker::semantic_decision  ALIAS   modules_perception_camera_lib_traffic_light_tracker_semantic_decision)

