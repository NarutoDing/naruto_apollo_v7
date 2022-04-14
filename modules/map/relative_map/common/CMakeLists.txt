cmake_minimum_required(VERSION 3.16)

project(modules_map_relative_map_common)
message("${Green} [info] modules_map_relative_map_common cmakelist ${ColourReset}")

add_library(modules_map_relative_map_common_relative_map_gflags  SHARED
  relative_map_gflags.cc
)
set_target_properties(modules_map_relative_map_common_relative_map_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_relative_map_common_relative_map_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::map::relative_map::common::relative_map_gflags  ALIAS   modules_map_relative_map_common_relative_map_gflags)

