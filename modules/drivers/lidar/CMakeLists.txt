cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar)
message("${Green} [info] modules_drivers_lidar cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_lidar_driver_component_lib  SHARED
  lidar_driver_component.cc
)
set_target_properties(modules_drivers_lidar_lidar_driver_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_lidar_driver_component_lib
  cyber::cyber
  modules::drivers::lidar::common::driver_factory::lidar_driver_factory
  modules::drivers::lidar::proto::config
)
add_library(modules::drivers::lidar::lidar_driver_component_lib  ALIAS   modules_drivers_lidar_lidar_driver_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(liblidar_driver_component  SHARED
  ${virtual_cc}
)
set_target_properties(liblidar_driver_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(liblidar_driver_component
  modules::drivers::lidar::lidar_driver_component_lib
)
