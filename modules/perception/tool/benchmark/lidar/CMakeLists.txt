cmake_minimum_required(VERSION 3.16)

project(modules_perception_tool_benchmark_lidar)
message("${Green} [info] modules_perception_tool_benchmark_lidar cmakelist ${ColourReset}")

add_library(modules_perception_tool_benchmark_lidar_benchmark_evaluation  SHARED
  detection_evaluation.cc
)
set_target_properties(modules_perception_tool_benchmark_lidar_benchmark_evaluation  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_benchmark_evaluation
  modules::perception::tool::benchmark::lidar::eval::benchmark_eval
  modules::perception::tool::benchmark::lidar::loader::benchmark_loader
)
add_library(modules::perception::tool::benchmark::lidar::benchmark_evaluation  ALIAS   modules_perception_tool_benchmark_lidar_benchmark_evaluation)

add_executable(lidar_benchmark
  lidar_detection_benchmark.cc
)
target_link_libraries(lidar_benchmark
  modules::perception::tool::benchmark::lidar::benchmark_evaluation
  third_party::boost
)
