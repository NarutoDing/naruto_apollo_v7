cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_robosense_driver)
message("${Green} [info] modules_drivers_lidar_robosense_driver cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_robosense_driver_robosense_driver_component_lib  SHARED
  robosense_driver_component.cc
)
set_target_properties(modules_drivers_lidar_robosense_driver_robosense_driver_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_robosense_driver_robosense_driver_component_lib
  modules::drivers::lidar::robosense::driver::driver
  cyber::cyber
)
add_library(modules::drivers::lidar::robosense::driver::robosense_driver_component_lib  ALIAS   modules_drivers_lidar_robosense_driver_robosense_driver_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_lidar_robosense_driver_driver  SHARED
  ${virtual_cc}
  driver.h
  utility.h
)
set_target_properties(modules_drivers_lidar_robosense_driver_driver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_robosense_driver_driver
  cyber::cyber
  modules::common::util::util
  modules::drivers::lidar::common::driver_factory::driver_base
  modules::drivers::lidar::proto::config_cc_proto
  modules::drivers::lidar::proto::robosense_cc_proto
  modules::drivers::lidar::robosense::decoder_factory
  modules::drivers::lidar::robosense::input::input
  modules::drivers::proto::pointcloud_cc_proto
)
add_library(modules::drivers::lidar::robosense::driver::driver  ALIAS   modules_drivers_lidar_robosense_driver_driver)

