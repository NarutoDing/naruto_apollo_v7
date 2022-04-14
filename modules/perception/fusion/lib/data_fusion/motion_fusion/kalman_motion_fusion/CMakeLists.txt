cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_data_fusion_motion_fusion_kalman_motion_fusion)
message("${Green} [info] modules_perception_fusion_lib_data_fusion_motion_fusion_kalman_motion_fusion cmakelist ${ColourReset}")

add_library(modules_perception_fusion_lib_data_fusion_motion_fusion_kalman_motion_fusion_kalman_motion_fusion  SHARED
  kalman_motion_fusion.cc
)
set_target_properties(modules_perception_fusion_lib_data_fusion_motion_fusion_kalman_motion_fusion_kalman_motion_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_data_fusion_motion_fusion_kalman_motion_fusion_kalman_motion_fusion
  modules::perception::base::base
  modules::perception::common::perception_gflags
  modules::perception::common::geometry::basic
  modules::perception::common::sensor_manager::sensor_manager
  modules::perception::fusion::base::base
  modules::perception::fusion::common::base_filter
  modules::perception::fusion::common::kalman_filter
  modules::perception::fusion::lib::interface::interface
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::fusion::lib::data_fusion::motion_fusion::kalman_motion_fusion::kalman_motion_fusion  ALIAS   modules_perception_fusion_lib_data_fusion_motion_fusion_kalman_motion_fusion_kalman_motion_fusion)

