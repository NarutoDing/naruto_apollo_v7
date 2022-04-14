cmake_minimum_required(VERSION 3.16)

project(modules_storytelling_common)
message("${Green} [info] modules_storytelling_common cmakelist ${ColourReset}")

add_library(modules_storytelling_common_storytelling_gflags  SHARED
  storytelling_gflags.cc
)
set_target_properties(modules_storytelling_common_storytelling_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_storytelling_common_storytelling_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::storytelling::common::storytelling_gflags  ALIAS   modules_storytelling_common_storytelling_gflags)

