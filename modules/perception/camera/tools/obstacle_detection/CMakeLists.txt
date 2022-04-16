cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_tools_obstacle_detection)
message("${Green} [info] modules_perception_camera_tools_obstacle_detection cmakelist ${ColourReset}")

add_executable(obstacle_detection
  obstacle_detection.cc
)
target_link_libraries(obstacle_detection
  modules::perception::base::base
  modules::perception::camera::lib::interface::interface
  modules::perception::common::io::io_util
  ${boost}
  
  ${opencv}
)
