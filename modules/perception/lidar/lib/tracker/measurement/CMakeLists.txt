cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_tracker_measurement)
message("${Green} [info] modules_perception_lidar_lib_tracker_measurement cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_tracker_measurement_measurement_collection  SHARED
  measurement_collection.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_measurement_measurement_collection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_measurement_measurement_collection
  modules::perception::common::geometry::basic
  modules::perception::common::geometry::common
  modules::perception::lidar::lib::tracker::common::tracked_object
)
add_library(modules::perception::lidar::lib::tracker::measurement::measurement_collection  ALIAS   modules_perception_lidar_lib_tracker_measurement_measurement_collection)

