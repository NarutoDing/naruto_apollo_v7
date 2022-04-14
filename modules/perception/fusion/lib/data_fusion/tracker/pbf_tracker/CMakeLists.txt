cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_data_fusion_tracker_pbf_tracker)
message("${Green} [info] modules_perception_fusion_lib_data_fusion_tracker_pbf_tracker cmakelist ${ColourReset}")

add_library(modules_perception_fusion_lib_data_fusion_tracker_pbf_tracker_pbf_tracker  SHARED
  pbf_tracker.cc
)
set_target_properties(modules_perception_fusion_lib_data_fusion_tracker_pbf_tracker_pbf_tracker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_data_fusion_tracker_pbf_tracker_pbf_tracker
  modules::common::util::string_util
  modules::perception::fusion::lib::data_fusion::existence_fusion::dst_existence_fusion::dst_existence_fusion
  modules::perception::fusion::lib::data_fusion::motion_fusion::kalman_motion_fusion::kalman_motion_fusion
  modules::perception::fusion::lib::data_fusion::shape_fusion::pbf_shape_fusion::pbf_shape_fusion
  modules::perception::fusion::lib::data_fusion::type_fusion::dst_type_fusion::dst_type_fusion
  modules::perception::fusion::lib::interface::interface
  modules::perception::proto::pbf_tracker_config_cc_proto
)
add_library(modules::perception::fusion::lib::data_fusion::tracker::pbf_tracker::pbf_tracker  ALIAS   modules_perception_fusion_lib_data_fusion_tracker_pbf_tracker_pbf_tracker)

