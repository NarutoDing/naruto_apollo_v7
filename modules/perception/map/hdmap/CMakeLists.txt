cmake_minimum_required(VERSION 3.16)

project(modules_perception_map_hdmap)
message("${Green} [info] modules_perception_map_hdmap cmakelist ${ColourReset}")

add_library(modules_perception_map_hdmap_hdmap_input  SHARED
  hdmap_input.cc
)
set_target_properties(modules_perception_map_hdmap_hdmap_input  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_map_hdmap_hdmap_input
  modules::common::math::geometry
  modules::map::hdmap::hdmap
  modules::perception::base::base_type
  modules::perception::base::blob
  modules::perception::base::common
  modules::perception::base::frame
  modules::perception::base::image
  modules::perception::base::impending_collision_edge
  modules::perception::base::object
  modules::perception::base::object_pool
  modules::perception::base::object_pool_types
  modules::perception::base::point_cloud
  modules::perception::base::syncedmem
  modules::perception::common::geometry::common
  modules::perception::lib::config_manager::config_manager
)
add_library(modules::perception::map::hdmap::hdmap_input  ALIAS   modules_perception_map_hdmap_hdmap_input)

