cmake_minimum_required(VERSION 3.16)

project(modules_perception_tool_benchmark_lidar_base)
message("${Green} [info] modules_perception_tool_benchmark_lidar_base cmakelist ${ColourReset}")

add_library(modules_perception_tool_benchmark_lidar_base_benchmark_base  SHARED
  frame.cc
  point_cloud_frame.cc
)
set_target_properties(modules_perception_tool_benchmark_lidar_base_benchmark_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_base_benchmark_base
  cyber::cyber
  modules::perception::tool::benchmark::lidar::util::benchmark_util
)
add_library(modules::perception::tool::benchmark::lidar::base::benchmark_base  ALIAS   modules_perception_tool_benchmark_lidar_base_benchmark_base)

