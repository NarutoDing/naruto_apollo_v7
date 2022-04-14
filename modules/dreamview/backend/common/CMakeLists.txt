cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_common)
message("${Green} [info] modules_dreamview_backend_common cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_common_dreamview_gflags  SHARED
  dreamview_gflags.cc
)
set_target_properties(modules_dreamview_backend_common_dreamview_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_common_dreamview_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::dreamview::backend::common::dreamview_gflags  ALIAS   modules_dreamview_backend_common_dreamview_gflags)

