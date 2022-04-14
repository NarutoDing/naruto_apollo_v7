cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_hesai)
message("${Green} [info] modules_drivers_lidar_hesai cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_hesai_hesai_convert_component  SHARED
  parser/hesai_convert_component.cc
)
set_target_properties(modules_drivers_lidar_hesai_hesai_convert_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_hesai_convert_component
  modules::drivers::lidar::hesai::parser_factory
  cyber::cyber
  modules::drivers::lidar::hesai::driver::driver
  modules::drivers::lidar::proto::hesai_config_cc_proto
)
add_library(modules::drivers::lidar::hesai::hesai_convert_component  ALIAS   modules_drivers_lidar_hesai_hesai_convert_component)

add_library(modules_drivers_lidar_hesai_parser_factory  SHARED
  parser/parser_factory.cc
)
set_target_properties(modules_drivers_lidar_hesai_parser_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_parser_factory
  modules::drivers::lidar::hesai::hesai40_parser
  modules::drivers::lidar::hesai::hesai64_parser
  modules::drivers::lidar::hesai::parser
  cyber::cyber
)
add_library(modules::drivers::lidar::hesai::parser_factory  ALIAS   modules_drivers_lidar_hesai_parser_factory)

add_library(modules_drivers_lidar_hesai_hesai64_parser  SHARED
  parser/hesai64_parser.cc
)
set_target_properties(modules_drivers_lidar_hesai_hesai64_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_hesai64_parser
  modules::drivers::lidar::hesai::parser
  cyber::cyber
)
add_library(modules::drivers::lidar::hesai::hesai64_parser  ALIAS   modules_drivers_lidar_hesai_hesai64_parser)

add_library(modules_drivers_lidar_hesai_hesai40_parser  SHARED
  parser/hesai40_parser.cc
)
set_target_properties(modules_drivers_lidar_hesai_hesai40_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_hesai40_parser
  modules::drivers::lidar::hesai::parser
  cyber::cyber
)
add_library(modules::drivers::lidar::hesai::hesai40_parser  ALIAS   modules_drivers_lidar_hesai_hesai40_parser)

add_library(modules_drivers_lidar_hesai_parser  SHARED
  parser/parser.cc
)
set_target_properties(modules_drivers_lidar_hesai_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_parser
  modules::drivers::lidar::hesai::tcp_cmd_client
  modules::drivers::lidar::hesai::type_defs
  cyber::cyber
  modules::drivers::lidar::proto::hesai_cc_proto
  modules::drivers::lidar::proto::hesai_config_cc_proto
  modules::drivers::proto::pointcloud_cc_proto
)
add_library(modules::drivers::lidar::hesai::parser  ALIAS   modules_drivers_lidar_hesai_parser)

add_library(modules_drivers_lidar_hesai_udp_input  SHARED
  input/udp_input.cc
)
set_target_properties(modules_drivers_lidar_hesai_udp_input  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_udp_input
  modules::drivers::lidar::hesai::type_defs
  cyber::cyber
)
add_library(modules::drivers::lidar::hesai::udp_input  ALIAS   modules_drivers_lidar_hesai_udp_input)

add_library(modules_drivers_lidar_hesai_tcp_cmd_client  SHARED
  parser/tcp_cmd_client.cc
)
set_target_properties(modules_drivers_lidar_hesai_tcp_cmd_client  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_tcp_cmd_client
  cyber::cyber
)
add_library(modules::drivers::lidar::hesai::tcp_cmd_client  ALIAS   modules_drivers_lidar_hesai_tcp_cmd_client)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_lidar_hesai_type_defs  SHARED
  ${virtual_cc}
  common/type_defs.h
)
set_target_properties(modules_drivers_lidar_hesai_type_defs  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_hesai_type_defs
  modules::drivers::lidar::hesai::const_var
)
add_library(modules::drivers::lidar::hesai::type_defs  ALIAS   modules_drivers_lidar_hesai_type_defs)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_lidar_hesai_const_var  SHARED
  ${virtual_cc}
  common/const_var.h
)
set_target_properties(modules_drivers_lidar_hesai_const_var  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::lidar::hesai::const_var  ALIAS   modules_drivers_lidar_hesai_const_var)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libhesai_driver_component  SHARED
  ${virtual_cc}
)
set_target_properties(libhesai_driver_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libhesai_driver_component
  modules::drivers::lidar::hesai::hesai_convert_component
  modules::drivers::lidar::hesai::driver::hesai_component
)
