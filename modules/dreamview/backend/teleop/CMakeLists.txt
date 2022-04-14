cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_teleop)
message("${Green} [info] modules_dreamview_backend_teleop cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_teleop_teleop  SHARED
  teleop.cc
)
set_target_properties(modules_dreamview_backend_teleop_teleop  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::dreamview::backend::teleop::teleop  ALIAS   modules_dreamview_backend_teleop_teleop)

