cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_lane_common)
message("${Green} [info] modules_perception_camera_lib_lane_common cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_lane_common_common_functions  SHARED
  common_functions.cc
)
set_target_properties(modules_perception_camera_lib_lane_common_common_functions  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_lane_common_common_functions
  cyber::cyber
  modules::perception::base::base
  ${eigen}
)
add_library(modules::perception::camera::lib::lane::common::common_functions  ALIAS   modules_perception_camera_lib_lane_common_common_functions)

