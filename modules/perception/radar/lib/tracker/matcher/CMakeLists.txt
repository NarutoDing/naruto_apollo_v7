cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_lib_tracker_matcher)
message("${Green} [info] modules_perception_radar_lib_tracker_matcher cmakelist ${ColourReset}")

add_library(modules_perception_radar_lib_tracker_matcher_hm_matcher  SHARED
  hm_matcher.cc
)
set_target_properties(modules_perception_radar_lib_tracker_matcher_hm_matcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_tracker_matcher_hm_matcher
  cyber::common::file
  modules::perception::base::base
  modules::perception::common::graph::graph
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::registerer::registerer
  modules::perception::proto::perception_config_schema_cc_proto
  modules::perception::proto::tracker_config_cc_proto
  modules::perception::radar::common::types
  modules::perception::radar::lib::interface::base_matcher
  modules::perception::radar::lib::tracker::common::radar_track
  ${absl}
  ${eigen}
)
add_library(modules::perception::radar::lib::tracker::matcher::hm_matcher  ALIAS   modules_perception_radar_lib_tracker_matcher_hm_matcher)

