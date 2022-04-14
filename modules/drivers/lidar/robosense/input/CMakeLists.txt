cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_robosense_input)
message("${Green} [info] modules_drivers_lidar_robosense_input cmakelist ${ColourReset}")

add_library(modules_drivers_lidar_robosense_input_input  SHARED
  input.cc
)
set_target_properties(modules_drivers_lidar_robosense_input_input  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::lidar::robosense::input::input  ALIAS   modules_drivers_lidar_robosense_input_input)

