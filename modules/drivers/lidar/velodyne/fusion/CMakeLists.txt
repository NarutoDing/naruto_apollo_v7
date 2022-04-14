cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_velodyne_fusion)
message("${Green} [info] modules_drivers_lidar_velodyne_fusion cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_velodyne_fusion_fusion_component_lib  SHARED
  pri_sec_fusion_component.cc
)
set_target_properties(modules_drivers_lidar_velodyne_fusion_fusion_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_velodyne_fusion_fusion_component_lib
  cyber::cyber
  modules::drivers::lidar::proto::velodyne_config_cc_proto
  modules::drivers::proto::pointcloud_cc_proto
  modules::transform::buffer
  ${eigen}
)
add_library(modules::drivers::lidar::velodyne::fusion::fusion_component_lib  ALIAS   modules_drivers_lidar_velodyne_fusion_fusion_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libvelodyne_fusion_component  SHARED
  ${virtual_cc}
)
set_target_properties(libvelodyne_fusion_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libvelodyne_fusion_component
  modules::drivers::lidar::velodyne::fusion::fusion_component_lib
)
