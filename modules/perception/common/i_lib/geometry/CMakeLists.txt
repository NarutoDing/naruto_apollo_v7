cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_i_lib_geometry)
message("${Green} [info] modules_perception_common_i_lib_geometry cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_i_lib_geometry_i_plane  SHARED
  ${virtual_cc}
  i_line.h
  i_plane.h
  i_util.h
)
set_target_properties(modules_perception_common_i_lib_geometry_i_plane  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_i_lib_geometry_i_plane
  ${eigen}
)
add_library(modules::perception::common::i_lib::geometry::i_plane  ALIAS   modules_perception_common_i_lib_geometry_i_plane)

