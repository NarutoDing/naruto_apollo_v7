cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_data_fusion_shape_fusion_pbf_shape_fusion)
message("${Green} [info] modules_perception_fusion_lib_data_fusion_shape_fusion_pbf_shape_fusion cmakelist ${ColourReset}")

add_library(modules_perception_fusion_lib_data_fusion_shape_fusion_pbf_shape_fusion_pbf_shape_fusion  SHARED
  pbf_shape_fusion.cc
)
set_target_properties(modules_perception_fusion_lib_data_fusion_shape_fusion_pbf_shape_fusion_pbf_shape_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_data_fusion_shape_fusion_pbf_shape_fusion_pbf_shape_fusion
  modules::perception::fusion::base::scene
  modules::perception::fusion::base::sensor_data_manager
  modules::perception::fusion::base::track
  modules::perception::fusion::lib::interface::interface
)
add_library(modules::perception::fusion::lib::data_fusion::shape_fusion::pbf_shape_fusion::pbf_shape_fusion  ALIAS   modules_perception_fusion_lib_data_fusion_shape_fusion_pbf_shape_fusion_pbf_shape_fusion)

