cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_common_driver_factory)
message("${Green} [info] modules_drivers_lidar_common_driver_factory cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_common_driver_factory_lidar_driver_factory  SHARED
  lidar_driver_factory.cc
)
set_target_properties(modules_drivers_lidar_common_driver_factory_lidar_driver_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_common_driver_factory_lidar_driver_factory
  modules::drivers::lidar::common::driver_factory::driver_base
  cyber::cyber
  modules::common::util::factory
  modules::drivers::lidar::hesai::driver::driver
  modules::drivers::lidar::proto::config_cc_proto
  modules::drivers::lidar::proto::lidar_parameter_cc_proto
  modules::drivers::lidar::robosense::driver::driver
  modules::drivers::lidar::velodyne::driver::driver
)
add_library(modules::drivers::lidar::common::driver_factory::lidar_driver_factory  ALIAS   modules_drivers_lidar_common_driver_factory_lidar_driver_factory)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_lidar_common_driver_factory_driver_base  SHARED
  ${virtual_cc}
  driver_base.h
)
set_target_properties(modules_drivers_lidar_common_driver_factory_driver_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_common_driver_factory_driver_base
  modules::common::util::util
  modules::common::util::factory
)
add_library(modules::drivers::lidar::common::driver_factory::driver_base  ALIAS   modules_drivers_lidar_common_driver_factory_driver_base)

