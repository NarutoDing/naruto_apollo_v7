cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_common)
message("${Green} [info] modules_perception_fusion_common cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_fusion_common_base_filter  SHARED
  ${virtual_cc}
  base_filter.h
)
set_target_properties(modules_perception_fusion_common_base_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_common_base_filter
  ${eigen}
)
add_library(modules::perception::fusion::common::base_filter  ALIAS   modules_perception_fusion_common_base_filter)

add_library(modules_perception_fusion_common_camera_util  SHARED
  camera_util.cc
)
set_target_properties(modules_perception_fusion_common_camera_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_common_camera_util
  modules::perception::base::camera
  modules::perception::common::geometry::common
  modules::perception::fusion::base::sensor
)
add_library(modules::perception::fusion::common::camera_util  ALIAS   modules_perception_fusion_common_camera_util)

add_library(modules_perception_fusion_common_dst_evidence  SHARED
  dst_evidence.cc
)
set_target_properties(modules_perception_fusion_common_dst_evidence  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_common_dst_evidence
  cyber::cyber
  ${boost}
)
add_library(modules::perception::fusion::common::dst_evidence  ALIAS   modules_perception_fusion_common_dst_evidence)

add_library(modules_perception_fusion_common_information_filter  SHARED
  information_filter.cc
)
set_target_properties(modules_perception_fusion_common_information_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_common_information_filter
  modules::perception::fusion::common::base_filter
)
add_library(modules::perception::fusion::common::information_filter  ALIAS   modules_perception_fusion_common_information_filter)

add_library(modules_perception_fusion_common_kalman_filter  SHARED
  kalman_filter.cc
)
set_target_properties(modules_perception_fusion_common_kalman_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_common_kalman_filter
  modules::perception::fusion::common::base_filter
  cyber::cyber
)
add_library(modules::perception::fusion::common::kalman_filter  ALIAS   modules_perception_fusion_common_kalman_filter)

