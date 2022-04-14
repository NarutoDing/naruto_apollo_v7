cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_velodyne_parser)
message("${Green} [info] modules_drivers_lidar_velodyne_parser cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_velodyne_parser_velodyne_convert_component_lib  SHARED
  velodyne_convert_component.cc
)
set_target_properties(modules_drivers_lidar_velodyne_parser_velodyne_convert_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_velodyne_parser_velodyne_convert_component_lib
  cyber::cyber
  modules::drivers::lidar::velodyne::parser::convert
)
add_library(modules::drivers::lidar::velodyne::parser::velodyne_convert_component_lib  ALIAS   modules_drivers_lidar_velodyne_parser_velodyne_convert_component_lib)

add_library(modules_drivers_lidar_velodyne_parser_convert  SHARED
  calibration.cc
  convert.cc
  online_calibration.cc
  util.cc
  velodyne128_parser.cc
  velodyne16_parser.cc
  velodyne32_parser.cc
  velodyne64_parser.cc
  velodyne_parser.cc
)
set_target_properties(modules_drivers_lidar_velodyne_parser_convert  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_velodyne_parser_convert
  cyber::cyber
  modules::drivers::lidar::proto::velodyne_config_cc_proto
  modules::drivers::proto::pointcloud_cc_proto
  ${boost}
  ${yaml}
  ${eigen}
)
add_library(modules::drivers::lidar::velodyne::parser::convert  ALIAS   modules_drivers_lidar_velodyne_parser_convert)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libvelodyne_convert_component  SHARED
  ${virtual_cc}
)
set_target_properties(libvelodyne_convert_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libvelodyne_convert_component
  modules::drivers::lidar::velodyne::parser::velodyne_convert_component_lib
)
