cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_lib_interface)
message("${Green} [info] modules_perception_radar_lib_interface cmakelist ${ColourReset}")

add_library(modules_perception_radar_lib_interface_base_matcher  SHARED
  base_matcher.cc
)
set_target_properties(modules_perception_radar_lib_interface_base_matcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_interface_base_matcher
  modules::perception::base::base
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::registerer::registerer
  modules::perception::proto::perception_config_schema_cc_proto
  modules::perception::radar::common::types
  modules::perception::radar::lib::tracker::common::radar_track
  
  ${eigen}
)
add_library(modules::perception::radar::lib::interface::base_matcher  ALIAS   modules_perception_radar_lib_interface_base_matcher)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_radar_lib_interface_base_filter  SHARED
  ${virtual_cc}
  base_filter.h
)
set_target_properties(modules_perception_radar_lib_interface_base_filter  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::radar::lib::interface::base_filter  ALIAS   modules_perception_radar_lib_interface_base_filter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_radar_lib_interface_base_detector  SHARED
  ${virtual_cc}
  base_detector.h
)
set_target_properties(modules_perception_radar_lib_interface_base_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_interface_base_detector
  modules::drivers::canbus::proto::can_card_parameter_cc_proto
  modules::drivers::proto::conti_radar_cc_proto
  modules::drivers::radar::conti_radar::proto::conti_radar_conf_cc_proto
)
add_library(modules::perception::radar::lib::interface::base_detector  ALIAS   modules_perception_radar_lib_interface_base_detector)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_radar_lib_interface_base_preprocessor  SHARED
  ${virtual_cc}
  base_preprocessor.h
)
set_target_properties(modules_perception_radar_lib_interface_base_preprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_interface_base_preprocessor
  modules::drivers::canbus::proto::can_card_parameter_cc_proto
  modules::drivers::proto::conti_radar_cc_proto
  modules::drivers::radar::conti_radar::proto::conti_radar_conf_cc_proto
)
add_library(modules::perception::radar::lib::interface::base_preprocessor  ALIAS   modules_perception_radar_lib_interface_base_preprocessor)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_radar_lib_interface_base_radar_obstacle_perception  SHARED
  ${virtual_cc}
  base_radar_obstacle_perception.h
)
set_target_properties(modules_perception_radar_lib_interface_base_radar_obstacle_perception  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::radar::lib::interface::base_radar_obstacle_perception  ALIAS   modules_perception_radar_lib_interface_base_radar_obstacle_perception)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_radar_lib_interface_base_roi_filter  SHARED
  ${virtual_cc}
  base_roi_filter.h
)
set_target_properties(modules_perception_radar_lib_interface_base_roi_filter  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::radar::lib::interface::base_roi_filter  ALIAS   modules_perception_radar_lib_interface_base_roi_filter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_radar_lib_interface_base_tracker  SHARED
  ${virtual_cc}
  base_tracker.h
)
set_target_properties(modules_perception_radar_lib_interface_base_tracker  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::radar::lib::interface::base_tracker  ALIAS   modules_perception_radar_lib_interface_base_tracker)

