cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_data_fusion_type_fusion_dst_type_fusion)
message("${Green} [info] modules_perception_fusion_lib_data_fusion_type_fusion_dst_type_fusion cmakelist ${ColourReset}")

add_library(modules_perception_fusion_lib_data_fusion_type_fusion_dst_type_fusion_dst_type_fusion  SHARED
  dst_type_fusion.cc
)
set_target_properties(modules_perception_fusion_lib_data_fusion_type_fusion_dst_type_fusion_dst_type_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_data_fusion_type_fusion_dst_type_fusion_dst_type_fusion
  cyber::common::file
  modules::perception::fusion::base::base_init_options
  modules::perception::fusion::base::scene
  modules::perception::fusion::base::sensor_data_manager
  modules::perception::fusion::base::track
  modules::perception::fusion::common::camera_util
  modules::perception::fusion::common::dst_evidence
  modules::perception::fusion::lib::interface::interface
  modules::perception::lib::config_manager::config_manager
  modules::perception::proto::dst_type_fusion_config_cc_proto
  ${absl}
)
add_library(modules::perception::fusion::lib::data_fusion::type_fusion::dst_type_fusion::dst_type_fusion  ALIAS   modules_perception_fusion_lib_data_fusion_type_fusion_dst_type_fusion_dst_type_fusion)

