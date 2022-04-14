cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_hesai_driver)
message("${Green} [info] modules_drivers_lidar_hesai_driver cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_hesai_driver_hesai_component  SHARED
  hesai_component.cc
)
set_target_properties(modules_drivers_lidar_hesai_driver_hesai_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_driver_hesai_component
  modules::drivers::lidar::hesai::driver::driver
  cyber::cyber
  modules::drivers::lidar::hesai::parser_factory
  modules::drivers::lidar::proto::hesai_config_cc_proto
)
add_library(modules::drivers::lidar::hesai::driver::hesai_component  ALIAS   modules_drivers_lidar_hesai_driver_hesai_component)

add_library(modules_drivers_lidar_hesai_driver_driver  SHARED
  driver.cc
)
set_target_properties(modules_drivers_lidar_hesai_driver_driver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_driver_driver
  cyber::cyber
  modules::drivers::lidar::common::driver_factory::driver_base
  modules::drivers::lidar::hesai::parser
  modules::drivers::lidar::hesai::parser_factory
  modules::drivers::lidar::hesai::type_defs
  modules::drivers::lidar::hesai::udp_input
  modules::drivers::lidar::proto::config_cc_proto
)
add_library(modules::drivers::lidar::hesai::driver::driver  ALIAS   modules_drivers_lidar_hesai_driver_driver)

