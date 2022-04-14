cmake_minimum_required(VERSION 3.16)

project(modules_perception_tool_benchmark_lidar_eval)
message("${Green} [info] modules_perception_tool_benchmark_lidar_eval cmakelist ${ColourReset}")

add_library(modules_perception_tool_benchmark_lidar_eval_benchmark_eval  SHARED
  frame_statistics.cc
  lidar_option.cc
  meta_statistics.cc
  position_metric.cc
  sequence_self_statistics.cc
)
set_target_properties(modules_perception_tool_benchmark_lidar_eval_benchmark_eval  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_eval_benchmark_eval
  cyber::cyber
  modules::perception::tool::benchmark::lidar::base::benchmark_base
  modules::perception::tool::benchmark::lidar::util::benchmark_util
)
add_library(modules::perception::tool::benchmark::lidar::eval::benchmark_eval  ALIAS   modules_perception_tool_benchmark_lidar_eval_benchmark_eval)

