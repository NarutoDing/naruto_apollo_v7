cmake_minimum_required(VERSION 3.16)

project(modules_perception_tool_benchmark_lidar_ctpl)
message("${Green} [info] modules_perception_tool_benchmark_lidar_ctpl cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_tool_benchmark_lidar_ctpl_benchmark_ctpl  SHARED
  ${virtual_cc}
  ctpl.h
  ctpl_stl.h
)
set_target_properties(modules_perception_tool_benchmark_lidar_ctpl_benchmark_ctpl  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::tool::benchmark::lidar::ctpl::benchmark_ctpl  ALIAS   modules_perception_tool_benchmark_lidar_ctpl_benchmark_ctpl)

