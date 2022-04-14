cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_point_cloud_processing)
message("${Green} [info] modules_perception_common_point_cloud_processing cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_point_cloud_processing_point_cloud_processing  SHARED
  ${virtual_cc}
  common.h
  downsampling.h
)
set_target_properties(modules_perception_common_point_cloud_processing_point_cloud_processing  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_point_cloud_processing_point_cloud_processing
  cyber::cyber
  modules::perception::base::point_cloud
  modules::perception::common::geometry::basic
)
add_library(modules::perception::common::point_cloud_processing::point_cloud_processing  ALIAS   modules_perception_common_point_cloud_processing_point_cloud_processing)

add_library(modules_perception_common_point_cloud_processing_point_cloud_processing_test  SHARED
  common_test.cc
  downsampling_test.cc
)
set_target_properties(modules_perception_common_point_cloud_processing_point_cloud_processing_test  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_point_cloud_processing_point_cloud_processing_test
  modules::perception::common::point_cloud_processing::point_cloud_processing
  
)
add_library(modules::perception::common::point_cloud_processing::point_cloud_processing_test  ALIAS   modules_perception_common_point_cloud_processing_point_cloud_processing_test)

