cmake_minimum_required(VERSION 3.16)

project(modules_tools_visualizer)
message("${Green} [info] modules_tools_visualizer cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_executable(cyber_visualizer
  ${virtual_cc}
)
target_link_libraries(cyber_visualizer
  modules::tools::visualizer::visualizer_lib
  ${fastrtps_LIB_DIR}/libfastrtps.so
  
)
