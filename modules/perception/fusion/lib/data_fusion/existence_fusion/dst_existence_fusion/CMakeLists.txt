cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_data_fusion_existence_fusion_dst_existence_fusion)
message("${Green} [info] modules_perception_fusion_lib_data_fusion_existence_fusion_dst_existence_fusion cmakelist ${ColourReset}")

add_library(modules_perception_fusion_lib_data_fusion_existence_fusion_dst_existence_fusion_dst_existence_fusion  SHARED
  dst_existence_fusion.cc
)
set_target_properties(modules_perception_fusion_lib_data_fusion_existence_fusion_dst_existence_fusion_dst_existence_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_data_fusion_existence_fusion_dst_existence_fusion_dst_existence_fusion
  modules::common::util::util
  modules::perception::fusion::base::base
  modules::perception::fusion::common::camera_util
  modules::perception::fusion::common::dst_evidence
  modules::perception::fusion::lib::interface::interface
  modules::perception::lib::registerer::registerer
  modules::perception::proto::dst_existence_fusion_config_cc_proto
)
add_library(modules::perception::fusion::lib::data_fusion::existence_fusion::dst_existence_fusion::dst_existence_fusion  ALIAS   modules_perception_fusion_lib_data_fusion_existence_fusion_dst_existence_fusion_dst_existence_fusion)

