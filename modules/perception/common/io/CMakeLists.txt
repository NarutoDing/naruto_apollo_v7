cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_io)
message("${Green} [info] modules_perception_common_io cmakelist ${ColourReset}")

add_library(modules_perception_common_io_io_util  SHARED
  io_util.cc
)
set_target_properties(modules_perception_common_io_io_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_io_io_util
  cyber::cyber
  modules::perception::base::camera
  modules::perception::base::distortion_model
  modules::perception::base::omnidirectional_model
  modules::perception::common::geometry::basic
  ${boost}
  ${yaml}
  ${absl}
  ${eigen}
)
add_library(modules::perception::common::io::io_util  ALIAS   modules_perception_common_io_io_util)

