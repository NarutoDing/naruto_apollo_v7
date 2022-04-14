cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_obstacle_transformer_multicue)
message("${Green} [info] modules_perception_camera_lib_obstacle_transformer_multicue cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_obstacle_transformer_multicue_obj_mapper  SHARED
  obj_mapper.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_transformer_multicue_obj_mapper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_transformer_multicue_obj_mapper
  cyber::cyber
  modules::perception::camera::common::common
  modules::perception::camera::common::proto::object_template_meta_schema_cc_proto
)
add_library(modules::perception::camera::lib::obstacle::transformer::multicue::obj_mapper  ALIAS   modules_perception_camera_lib_obstacle_transformer_multicue_obj_mapper)

add_library(modules_perception_camera_lib_obstacle_transformer_multicue_multicue_obstacle_transformer  SHARED
  multicue_obstacle_transformer.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_transformer_multicue_multicue_obstacle_transformer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_transformer_multicue_multicue_obstacle_transformer
  modules::perception::camera::lib::obstacle::transformer::multicue::obj_mapper
  cyber::cyber
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::obstacle::transformer::multicue::proto::multicue_cc_proto
  
)
add_library(modules::perception::camera::lib::obstacle::transformer::multicue::multicue_obstacle_transformer  ALIAS   modules_perception_camera_lib_obstacle_transformer_multicue_multicue_obstacle_transformer)

