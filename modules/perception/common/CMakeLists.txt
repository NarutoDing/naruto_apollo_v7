cmake_minimum_required(VERSION 3.16)

project(modules_perception_common)
message("${Green} [info] modules_perception_common cmakelist ${ColourReset}")

add_library(modules_perception_common_perception_gflags  SHARED
  perception_gflags.cc
)
set_target_properties(modules_perception_common_perception_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_perception_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::perception::common::perception_gflags  ALIAS   modules_perception_common_perception_gflags)

