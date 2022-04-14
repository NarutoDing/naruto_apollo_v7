cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_interface)
message("${Green} [info] modules_perception_lidar_lib_interface cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_interface  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_lidar_lib_interface_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_interface
  modules::perception::lidar::lib::interface::base_bipartite_graph_matcher
  modules::perception::lidar::lib::interface::base_classifier
  modules::perception::lidar::lib::interface::base_ground_detector
  modules::perception::lidar::lib::interface::base_multi_target_tracker
  modules::perception::lidar::lib::interface::base_object_filter
  modules::perception::lidar::lib::interface::base_roi_filter
  modules::perception::lidar::lib::interface::base_lidar_detector
  modules::perception::lidar::lib::interface::base_pointcloud_preprocessor
  modules::perception::lidar::lib::interface::base_lidar_obstacle_tracking
)
add_library(modules::perception::lidar::lib::interface::interface  ALIAS   modules_perception_lidar_lib_interface_interface)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_bipartite_graph_matcher  SHARED
  ${virtual_cc}
  base_bipartite_graph_matcher.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_bipartite_graph_matcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_bipartite_graph_matcher
  modules::perception::common::graph::secure_matrix
  modules::perception::lib::registerer::registerer
  ${eigen}
)
add_library(modules::perception::lidar::lib::interface::base_bipartite_graph_matcher  ALIAS   modules_perception_lidar_lib_interface_base_bipartite_graph_matcher)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_lidar_detector  SHARED
  ${virtual_cc}
  base_lidar_detector.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_lidar_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_lidar_detector
  cyber::common::macros
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::lidar_frame
)
add_library(modules::perception::lidar::lib::interface::base_lidar_detector  ALIAS   modules_perception_lidar_lib_interface_base_lidar_detector)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_lidar_obstacle_detection  SHARED
  ${virtual_cc}
  base_lidar_obstacle_detection.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_lidar_obstacle_detection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_lidar_obstacle_detection
  cyber::common::macros
  modules::perception::lidar::common::lidar_error_code
  modules::perception::lib::registerer::registerer
  modules::drivers::proto::pointcloud_cc_proto
  modules::perception::lidar::common::lidar_frame
  ${eigen}
)
add_library(modules::perception::lidar::lib::interface::base_lidar_obstacle_detection  ALIAS   modules_perception_lidar_lib_interface_base_lidar_obstacle_detection)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_lidar_obstacle_tracking  SHARED
  ${virtual_cc}
  base_lidar_obstacle_tracking.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_lidar_obstacle_tracking  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_lidar_obstacle_tracking
  cyber::common::macros
  modules::perception::lidar::common::lidar_error_code
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::lidar_frame
)
add_library(modules::perception::lidar::lib::interface::base_lidar_obstacle_tracking  ALIAS   modules_perception_lidar_lib_interface_base_lidar_obstacle_tracking)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_pointcloud_preprocessor  SHARED
  ${virtual_cc}
  base_pointcloud_preprocessor.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_pointcloud_preprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_pointcloud_preprocessor
  cyber::common::macros
  modules::perception::lib::registerer::registerer
  modules::drivers::proto::pointcloud_cc_proto
  modules::perception::lidar::common::lidar_frame
)
add_library(modules::perception::lidar::lib::interface::base_pointcloud_preprocessor  ALIAS   modules_perception_lidar_lib_interface_base_pointcloud_preprocessor)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_classifier  SHARED
  ${virtual_cc}
  base_classifier.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_classifier  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_classifier
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::lidar_frame
)
add_library(modules::perception::lidar::lib::interface::base_classifier  ALIAS   modules_perception_lidar_lib_interface_base_classifier)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_ground_detector  SHARED
  ${virtual_cc}
  base_ground_detector.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_ground_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_ground_detector
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::lidar_frame
)
add_library(modules::perception::lidar::lib::interface::base_ground_detector  ALIAS   modules_perception_lidar_lib_interface_base_ground_detector)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_multi_target_tracker  SHARED
  ${virtual_cc}
  base_multi_target_tracker.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_multi_target_tracker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_multi_target_tracker
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::lidar_frame
)
add_library(modules::perception::lidar::lib::interface::base_multi_target_tracker  ALIAS   modules_perception_lidar_lib_interface_base_multi_target_tracker)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_object_filter  SHARED
  ${virtual_cc}
  base_object_filter.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_object_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_object_filter
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::lidar_frame
)
add_library(modules::perception::lidar::lib::interface::base_object_filter  ALIAS   modules_perception_lidar_lib_interface_base_object_filter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_interface_base_roi_filter  SHARED
  ${virtual_cc}
  base_roi_filter.h
)
set_target_properties(modules_perception_lidar_lib_interface_base_roi_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_interface_base_roi_filter
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::lidar_frame
)
add_library(modules::perception::lidar::lib::interface::base_roi_filter  ALIAS   modules_perception_lidar_lib_interface_base_roi_filter)

