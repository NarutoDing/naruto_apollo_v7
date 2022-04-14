cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_velodyne_compensator)
message("${Green} [info] modules_drivers_lidar_velodyne_compensator cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_velodyne_compensator_compensator_component_lib  SHARED
  compensator_component.cc
)
set_target_properties(modules_drivers_lidar_velodyne_compensator_compensator_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_velodyne_compensator_compensator_component_lib
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::latency_recorder::latency_recorder
  modules::drivers::lidar::proto::velodyne_cc_proto
  modules::drivers::lidar::velodyne::compensator::compensator_lib
)
add_library(modules::drivers::lidar::velodyne::compensator::compensator_component_lib  ALIAS   modules_drivers_lidar_velodyne_compensator_compensator_component_lib)

add_library(modules_drivers_lidar_velodyne_compensator_compensator_lib  SHARED
  compensator.cc
)
set_target_properties(modules_drivers_lidar_velodyne_compensator_compensator_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_velodyne_compensator_compensator_lib
  modules::drivers::lidar::proto::velodyne_config_cc_proto
  modules::drivers::proto::pointcloud_cc_proto
  modules::transform::buffer
  ${eigen}
)
add_library(modules::drivers::lidar::velodyne::compensator::compensator_lib  ALIAS   modules_drivers_lidar_velodyne_compensator_compensator_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libvelodyne_compensator_component  SHARED
  ${virtual_cc}
)
set_target_properties(libvelodyne_compensator_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libvelodyne_compensator_component
  modules::drivers::lidar::velodyne::compensator::compensator_component_lib
)
