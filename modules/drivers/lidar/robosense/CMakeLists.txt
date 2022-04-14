cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_robosense)
message("${Green} [info] modules_drivers_lidar_robosense cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_lidar_robosense_decoder_factory  SHARED
  ${virtual_cc}
  decoder/decoder_base.hpp
  decoder/decoder_factory.hpp
)
set_target_properties(modules_drivers_lidar_robosense_decoder_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_robosense_decoder_factory
  modules::drivers::lidar::robosense::decoder_128
  modules::drivers::lidar::robosense::decoder_16
  modules::drivers::lidar::robosense::decoder_32
  modules::drivers::lidar::robosense::decoder_bp
)
add_library(modules::drivers::lidar::robosense::decoder_factory  ALIAS   modules_drivers_lidar_robosense_decoder_factory)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_lidar_robosense_decoder_16  SHARED
  ${virtual_cc}
  decoder/decoder_16.hpp
)
set_target_properties(modules_drivers_lidar_robosense_decoder_16  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::lidar::robosense::decoder_16  ALIAS   modules_drivers_lidar_robosense_decoder_16)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_lidar_robosense_decoder_32  SHARED
  ${virtual_cc}
  decoder/decoder_32.hpp
)
set_target_properties(modules_drivers_lidar_robosense_decoder_32  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::lidar::robosense::decoder_32  ALIAS   modules_drivers_lidar_robosense_decoder_32)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_lidar_robosense_decoder_128  SHARED
  ${virtual_cc}
  decoder/decoder_128.hpp
)
set_target_properties(modules_drivers_lidar_robosense_decoder_128  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::lidar::robosense::decoder_128  ALIAS   modules_drivers_lidar_robosense_decoder_128)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_lidar_robosense_decoder_bp  SHARED
  ${virtual_cc}
  decoder/decoder_bp.hpp
)
set_target_properties(modules_drivers_lidar_robosense_decoder_bp  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::lidar::robosense::decoder_bp  ALIAS   modules_drivers_lidar_robosense_decoder_bp)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(librobosense_driver_component  SHARED
  ${virtual_cc}
)
set_target_properties(librobosense_driver_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(librobosense_driver_component
  modules::drivers::lidar::robosense::driver::robosense_driver_component_lib
)
