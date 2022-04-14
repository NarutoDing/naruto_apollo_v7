cmake_minimum_required(VERSION 3.16)

project(modules_prediction_container_pose)
message("${Green} [info] modules_prediction_container_pose cmakelist ${ColourReset}")

add_library(modules_prediction_container_pose_pose_container  SHARED
  pose_container.cc
)
set_target_properties(modules_prediction_container_pose_pose_container  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_container_pose_pose_container
  modules::common::math::quaternion
  modules::localization::proto::localization_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
  modules::prediction::common::prediction_gflags
  modules::prediction::container::container
)
add_library(modules::prediction::container::pose::pose_container  ALIAS   modules_prediction_container_pose_pose_container)

