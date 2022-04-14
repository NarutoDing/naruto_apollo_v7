cmake_minimum_required(VERSION 3.16)

project(modules_perception_tool_benchmark_lidar_util)
message("${Green} [info] modules_perception_tool_benchmark_lidar_util cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_tool_benchmark_lidar_util_types  SHARED
  ${virtual_cc}
  types.h
)
set_target_properties(modules_perception_tool_benchmark_lidar_util_types  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_util_types
  ${pcl}
)
add_library(modules::perception::tool::benchmark::lidar::util::types  ALIAS   modules_perception_tool_benchmark_lidar_util_types)

add_library(modules_perception_tool_benchmark_lidar_util_object_supplement  SHARED
  object_supplement.cc
)
set_target_properties(modules_perception_tool_benchmark_lidar_util_object_supplement  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_util_object_supplement
  ${eigen}
)
add_library(modules::perception::tool::benchmark::lidar::util::object_supplement  ALIAS   modules_perception_tool_benchmark_lidar_util_object_supplement)

add_library(modules_perception_tool_benchmark_lidar_util_object  SHARED
  object.cc
)
set_target_properties(modules_perception_tool_benchmark_lidar_util_object  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_util_object
  modules::perception::tool::benchmark::lidar::util::object_supplement
  modules::perception::tool::benchmark::lidar::util::types
  modules::common::util::string_util
  ${absl}
  ${eigen}
  ${pcl}
)
add_library(modules::perception::tool::benchmark::lidar::util::object  ALIAS   modules_perception_tool_benchmark_lidar_util_object)

add_library(modules_perception_tool_benchmark_lidar_util_geo_util  SHARED
  geo_util.cc
)
set_target_properties(modules_perception_tool_benchmark_lidar_util_geo_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_util_geo_util
  modules::perception::tool::benchmark::lidar::util::types
  ${eigen}
)
add_library(modules::perception::tool::benchmark::lidar::util::geo_util  ALIAS   modules_perception_tool_benchmark_lidar_util_geo_util)

add_library(modules_perception_tool_benchmark_lidar_util_io_util  SHARED
  io_util.cc
)
set_target_properties(modules_perception_tool_benchmark_lidar_util_io_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_util_io_util
  modules::perception::tool::benchmark::lidar::util::geo_util
  modules::perception::tool::benchmark::lidar::util::object
  ${pcl}
)
add_library(modules::perception::tool::benchmark::lidar::util::io_util  ALIAS   modules_perception_tool_benchmark_lidar_util_io_util)

add_library(modules_perception_tool_benchmark_lidar_util_  SHARED
  visibility.cc
)
set_target_properties(modules_perception_tool_benchmark_lidar_util_  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_util_
  modules::perception::tool::benchmark::lidar::util::geo_util
  modules::perception::tool::benchmark::lidar::util::object
)
add_library(modules::perception::tool::benchmark::lidar::util::  ALIAS   modules_perception_tool_benchmark_lidar_util_)

add_library(modules_perception_tool_benchmark_lidar_util_option_parser  SHARED
  option_parser.cc
)
set_target_properties(modules_perception_tool_benchmark_lidar_util_option_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_util_option_parser
  modules::common::util::string_util
  ${absl}
)
add_library(modules::perception::tool::benchmark::lidar::util::option_parser  ALIAS   modules_perception_tool_benchmark_lidar_util_option_parser)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_tool_benchmark_lidar_util_benchmark_util  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_tool_benchmark_lidar_util_benchmark_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_util_benchmark_util
  modules::perception::tool::benchmark::lidar::util::geo_util
  modules::perception::tool::benchmark::lidar::util::io_util
  modules::perception::tool::benchmark::lidar::util::object
  modules::perception::tool::benchmark::lidar::util::object_supplement
  modules::perception::tool::benchmark::lidar::util::option_parser
)
add_library(modules::perception::tool::benchmark::lidar::util::benchmark_util  ALIAS   modules_perception_tool_benchmark_lidar_util_benchmark_util)

