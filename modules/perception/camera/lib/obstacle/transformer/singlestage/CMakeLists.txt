cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_obstacle_transformer_singlestage)
message("${Green} [info] modules_perception_camera_lib_obstacle_transformer_singlestage cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_obstacle_transformer_singlestage_singlestage_obstacle_transformer  SHARED
  singlestage_obstacle_transformer.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_transformer_singlestage_singlestage_obstacle_transformer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_transformer_singlestage_singlestage_obstacle_transformer
  cyber::cyber
  modules::perception::camera::common::common
  modules::perception::camera::common::object_template_manager
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::obstacle::transformer::singlestage::proto::singlestage_cc_proto
  modules::perception::common::i_lib::core::core
)
add_library(modules::perception::camera::lib::obstacle::transformer::singlestage::singlestage_obstacle_transformer  ALIAS   modules_perception_camera_lib_obstacle_transformer_singlestage_singlestage_obstacle_transformer)

