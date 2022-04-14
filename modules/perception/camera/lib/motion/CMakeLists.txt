cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_motion)
message("${Green} [info] modules_perception_camera_lib_motion cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_motion_motion  SHARED
  plane_motion.cc
)
set_target_properties(modules_perception_camera_lib_motion_motion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_motion_motion
  modules::perception::base::base
)
add_library(modules::perception::camera::lib::motion::motion  ALIAS   modules_perception_camera_lib_motion_motion)

