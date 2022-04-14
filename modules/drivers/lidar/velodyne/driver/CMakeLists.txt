cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_velodyne_driver)
message("${Green} [info] modules_drivers_lidar_velodyne_driver cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_velodyne_driver_velodyne_driver_component_lib  SHARED
  velodyne_driver_component.cc
)
set_target_properties(modules_drivers_lidar_velodyne_driver_velodyne_driver_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_velodyne_driver_velodyne_driver_component_lib
  cyber::cyber
  modules::common::util::message_util
  modules::drivers::lidar::velodyne::driver::driver
)
add_library(modules::drivers::lidar::velodyne::driver::velodyne_driver_component_lib  ALIAS   modules_drivers_lidar_velodyne_driver_velodyne_driver_component_lib)

add_library(modules_drivers_lidar_velodyne_driver_driver  SHARED
  driver.cc
  driver64.cc
  input.cc
  socket_input.cc
)
set_target_properties(modules_drivers_lidar_velodyne_driver_driver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_velodyne_driver_driver
  cyber::cyber
  modules::common::util::message_util
  modules::drivers::lidar::common::driver_factory::driver_base
  modules::drivers::lidar::proto::config_cc_proto
  modules::drivers::lidar::proto::velodyne_config_cc_proto
)
add_library(modules::drivers::lidar::velodyne::driver::driver  ALIAS   modules_drivers_lidar_velodyne_driver_driver)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libvelodyne_driver_component  SHARED
  ${virtual_cc}
)
set_target_properties(libvelodyne_driver_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libvelodyne_driver_component
  modules::drivers::lidar::velodyne::driver::velodyne_driver_component_lib
)
