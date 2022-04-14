cmake_minimum_required(VERSION 3.16)

project(modules_perception_tool_benchmark_lidar_loader)
message("${Green} [info] modules_perception_tool_benchmark_lidar_loader cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_tool_benchmark_lidar_loader_benchmark_loader  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_tool_benchmark_lidar_loader_benchmark_loader  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_tool_benchmark_lidar_loader_benchmark_loader
  modules::perception::tool::benchmark::lidar::ctpl::benchmark_ctpl
)
add_library(modules::perception::tool::benchmark::lidar::loader::benchmark_loader  ALIAS   modules_perception_tool_benchmark_lidar_loader_benchmark_loader)

