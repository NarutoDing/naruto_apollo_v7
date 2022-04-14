cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_lib_tracker_conti_ars_tracker)
message("${Green} [info] modules_perception_radar_lib_tracker_conti_ars_tracker cmakelist ${ColourReset}")

add_library(modules_perception_radar_lib_tracker_conti_ars_tracker_conti_ars_tracker  SHARED
  conti_ars_tracker.cc
)
set_target_properties(modules_perception_radar_lib_tracker_conti_ars_tracker_conti_ars_tracker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_tracker_conti_ars_tracker_conti_ars_tracker
  modules::perception::base::base
  modules::perception::common::graph::graph
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::registerer::registerer
  modules::perception::proto::perception_config_schema_cc_proto
  modules::perception::radar::common::types
  modules::perception::radar::lib::interface::base_matcher
  modules::perception::radar::lib::interface::base_tracker
  modules::perception::radar::lib::tracker::common::radar_track_manager
  modules::perception::radar::lib::tracker::matcher::hm_matcher
  ${eigen}
  
)
add_library(modules::perception::radar::lib::tracker::conti_ars_tracker::conti_ars_tracker  ALIAS   modules_perception_radar_lib_tracker_conti_ars_tracker_conti_ars_tracker)

