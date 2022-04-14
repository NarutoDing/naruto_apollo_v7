cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_common)
message("${Green} [info] modules_perception_lidar_common cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_common_common  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_lidar_common_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_common_common
  modules::perception::lidar::common::cloud_mask
  modules::perception::lidar::common::lidar_error_code
  modules::perception::lidar::common::lidar_frame
  modules::perception::lidar::common::lidar_log
  modules::perception::lidar::common::lidar_object_util
  modules::perception::lidar::common::lidar_point_label
  modules::perception::lidar::common::lidar_timer
  modules::perception::lidar::common::pcl_util
)
add_library(modules::perception::lidar::common::common  ALIAS   modules_perception_lidar_common_common)

add_library(modules_perception_lidar_common_cloud_mask  SHARED
  cloud_mask.cc
)
set_target_properties(modules_perception_lidar_common_cloud_mask  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_common_cloud_mask
  modules::perception::base::point_cloud
)
add_library(modules::perception::lidar::common::cloud_mask  ALIAS   modules_perception_lidar_common_cloud_mask)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_common_lidar_log  SHARED
  ${virtual_cc}
  lidar_log.h
)
set_target_properties(modules_perception_lidar_common_lidar_log  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_common_lidar_log
  cyber::cyber
)
add_library(modules::perception::lidar::common::lidar_log  ALIAS   modules_perception_lidar_common_lidar_log)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_common_feature_descriptor  SHARED
  ${virtual_cc}
  feature_descriptor.h
)
set_target_properties(modules_perception_lidar_common_feature_descriptor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_common_feature_descriptor
  cyber::cyber
  modules::perception::base::point_cloud
)
add_library(modules::perception::lidar::common::feature_descriptor  ALIAS   modules_perception_lidar_common_feature_descriptor)

add_library(modules_perception_lidar_common_lidar_frame  SHARED
  lidar_frame_pool.cc
)
set_target_properties(modules_perception_lidar_common_lidar_frame  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_common_lidar_frame
  modules::perception::lidar::common::lidar_log
  modules::perception::base::base
)
add_library(modules::perception::lidar::common::lidar_frame  ALIAS   modules_perception_lidar_common_lidar_frame)

add_library(modules_perception_lidar_common_lidar_object_util  SHARED
  lidar_object_util.cc
)
set_target_properties(modules_perception_lidar_common_lidar_object_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_common_lidar_object_util
  modules::perception::lidar::common::lidar_log
  modules::perception::base::base
)
add_library(modules::perception::lidar::common::lidar_object_util  ALIAS   modules_perception_lidar_common_lidar_object_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_common_lidar_point_label  SHARED
  ${virtual_cc}
  lidar_point_label.h
)
set_target_properties(modules_perception_lidar_common_lidar_point_label  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::common::lidar_point_label  ALIAS   modules_perception_lidar_common_lidar_point_label)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_common_lidar_timer  SHARED
  ${virtual_cc}
  lidar_timer.h
)
set_target_properties(modules_perception_lidar_common_lidar_timer  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::common::lidar_timer  ALIAS   modules_perception_lidar_common_lidar_timer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_common_lidar_error_code  SHARED
  ${virtual_cc}
  lidar_error_code.h
)
set_target_properties(modules_perception_lidar_common_lidar_error_code  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::common::lidar_error_code  ALIAS   modules_perception_lidar_common_lidar_error_code)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_common_pcl_util  SHARED
  ${virtual_cc}
  pcl_util.h
)
set_target_properties(modules_perception_lidar_common_pcl_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_common_pcl_util
  modules::perception::lidar::common::lidar_log
  modules::perception::base::base
  ${pcl}
)
add_library(modules::perception::lidar::common::pcl_util  ALIAS   modules_perception_lidar_common_pcl_util)

add_library(modules_perception_lidar_common_object_sequence  SHARED
  object_sequence.cc
)
set_target_properties(modules_perception_lidar_common_object_sequence  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_common_object_sequence
  cyber::cyber
  modules::perception::base::object
  modules::perception::lidar::common::common
  
)
add_library(modules::perception::lidar::common::object_sequence  ALIAS   modules_perception_lidar_common_object_sequence)

