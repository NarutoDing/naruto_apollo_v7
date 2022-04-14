cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_obstacle_postprocessor_location_refiner)
message("${Green} [info] modules_perception_camera_lib_obstacle_postprocessor_location_refiner cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_obstacle_postprocessor_location_refiner_location_refiner_obstacle_postprocessor  SHARED
  location_refiner_obstacle_postprocessor.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_postprocessor_location_refiner_location_refiner_obstacle_postprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_postprocessor_location_refiner_location_refiner_obstacle_postprocessor
  modules::perception::camera::lib::obstacle::postprocessor::location_refiner::obj_postprocessor
  cyber::cyber
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::obstacle::postprocessor::location_refiner::proto::location_refiner_cc_proto
  
)
add_library(modules::perception::camera::lib::obstacle::postprocessor::location_refiner::location_refiner_obstacle_postprocessor  ALIAS   modules_perception_camera_lib_obstacle_postprocessor_location_refiner_location_refiner_obstacle_postprocessor)

add_library(modules_perception_camera_lib_obstacle_postprocessor_location_refiner_obj_postprocessor  SHARED
  obj_postprocessor.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_postprocessor_location_refiner_obj_postprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_postprocessor_location_refiner_obj_postprocessor
  modules::perception::camera::common::common
)
add_library(modules::perception::camera::lib::obstacle::postprocessor::location_refiner::obj_postprocessor  ALIAS   modules_perception_camera_lib_obstacle_postprocessor_location_refiner_obj_postprocessor)

