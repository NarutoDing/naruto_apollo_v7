cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend)
message("${Green} [info] modules_dreamview_backend cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_backend  SHARED
  dreamview.cc
)
set_target_properties(modules_dreamview_backend_backend  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::dreamview::backend::backend  ALIAS   modules_dreamview_backend_backend)

