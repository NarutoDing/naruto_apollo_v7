cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_object_builder)
message("${Green} [info] modules_perception_lidar_lib_object_builder cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_object_builder_object_builder  SHARED
  object_builder.cc
)
set_target_properties(modules_perception_lidar_lib_object_builder_object_builder  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_object_builder_object_builder
  modules::perception::base::base
  modules::perception::common::geometry::common
  modules::perception::common::geometry::convex_hull_2d
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::registerer::registerer
  modules::perception::lidar::common::lidar_frame
)
add_library(modules::perception::lidar::lib::object_builder::object_builder  ALIAS   modules_perception_lidar_lib_object_builder_object_builder)

