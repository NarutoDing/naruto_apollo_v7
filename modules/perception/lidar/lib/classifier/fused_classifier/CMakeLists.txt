cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_classifier_fused_classifier)
message("${Green} [info] modules_perception_lidar_lib_classifier_fused_classifier cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_classifier_fused_classifier_util  SHARED
  util.cc
)
set_target_properties(modules_perception_lidar_lib_classifier_fused_classifier_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_classifier_fused_classifier_util
  cyber::cyber
  modules::common::util::eigen_defs
  modules::perception::base::object
  ${eigen}
)
add_library(modules::perception::lidar::lib::classifier::fused_classifier::util  ALIAS   modules_perception_lidar_lib_classifier_fused_classifier_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_classifier_fused_classifier_type_fusion_interface  SHARED
  ${virtual_cc}
  type_fusion_interface.h
)
set_target_properties(modules_perception_lidar_lib_classifier_fused_classifier_type_fusion_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_classifier_fused_classifier_type_fusion_interface
  modules::perception::base::object
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::common
)
add_library(modules::perception::lidar::lib::classifier::fused_classifier::type_fusion_interface  ALIAS   modules_perception_lidar_lib_classifier_fused_classifier_type_fusion_interface)

add_library(modules_perception_lidar_lib_classifier_fused_classifier_ccrf_type_fusion  SHARED
  ccrf_type_fusion.cc
)
set_target_properties(modules_perception_lidar_lib_classifier_fused_classifier_ccrf_type_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_classifier_fused_classifier_ccrf_type_fusion
  modules::perception::lidar::lib::classifier::fused_classifier::type_fusion_interface
  modules::perception::lidar::lib::classifier::fused_classifier::util
  cyber::cyber
  modules::common::util::eigen_defs
  modules::perception::base::object
  modules::perception::base::point_cloud
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::common::object_sequence
  modules::perception::proto::ccrf_type_fusion_config_cc_proto
  
)
add_library(modules::perception::lidar::lib::classifier::fused_classifier::ccrf_type_fusion  ALIAS   modules_perception_lidar_lib_classifier_fused_classifier_ccrf_type_fusion)

add_library(modules_perception_lidar_lib_classifier_fused_classifier_fused_classifier  SHARED
  fused_classifier.cc
)
set_target_properties(modules_perception_lidar_lib_classifier_fused_classifier_fused_classifier  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_classifier_fused_classifier_fused_classifier
  modules::perception::lidar::lib::classifier::fused_classifier::type_fusion_interface
  cyber::cyber
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::common::lidar_frame
  modules::perception::lidar::common::object_sequence
  modules::perception::lidar::lib::interface::base_classifier
  modules::perception::proto::fused_classifier_config_cc_proto
  
)
add_library(modules::perception::lidar::lib::classifier::fused_classifier::fused_classifier  ALIAS   modules_perception_lidar_lib_classifier_fused_classifier_fused_classifier)

add_library(modules_perception_lidar_lib_classifier_fused_classifier_fused_classifier_test  SHARED
  fused_classifier_test.cc
)
set_target_properties(modules_perception_lidar_lib_classifier_fused_classifier_fused_classifier_test  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_classifier_fused_classifier_fused_classifier_test
  modules::perception::lidar::lib::classifier::fused_classifier::fused_classifier
  modules::perception::lidar::lib::classifier::fused_classifier::util
  
)
add_library(modules::perception::lidar::lib::classifier::fused_classifier::fused_classifier_test  ALIAS   modules_perception_lidar_lib_classifier_fused_classifier_fused_classifier_test)

