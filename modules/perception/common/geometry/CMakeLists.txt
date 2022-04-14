cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_geometry)
message("${Green} [info] modules_perception_common_geometry cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_geometry_basic  SHARED
  ${virtual_cc}
  basic.h
)
set_target_properties(modules_perception_common_geometry_basic  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_geometry_basic
  modules::perception::common::geometry::common
  ${eigen}
)
add_library(modules::perception::common::geometry::basic  ALIAS   modules_perception_common_geometry_basic)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_geometry_common  SHARED
  ${virtual_cc}
  common.h
)
set_target_properties(modules_perception_common_geometry_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_geometry_common
  modules::common::util::eigen_defs
  modules::perception::base::box
  modules::perception::base::point_cloud
)
add_library(modules::perception::common::geometry::common  ALIAS   modules_perception_common_geometry_common)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_geometry_convex_hull_2d  SHARED
  ${virtual_cc}
  convex_hull_2d.h
)
set_target_properties(modules_perception_common_geometry_convex_hull_2d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_geometry_convex_hull_2d
  ${eigen}
)
add_library(modules::perception::common::geometry::convex_hull_2d  ALIAS   modules_perception_common_geometry_convex_hull_2d)

add_library(modules_perception_common_geometry_roi_filter  SHARED
  roi_filter.cc
)
set_target_properties(modules_perception_common_geometry_roi_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_geometry_roi_filter
  modules::perception::common::geometry::common
  modules::perception::base::base_type
  modules::perception::base::object
  modules::perception::base::point_cloud
  ${eigen}
)
add_library(modules::perception::common::geometry::roi_filter  ALIAS   modules_perception_common_geometry_roi_filter)

add_library(modules_perception_common_geometry_camera_homography  SHARED
  camera_homography.cc
)
set_target_properties(modules_perception_common_geometry_camera_homography  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_geometry_camera_homography
  modules::perception::base::camera
  ${eigen}
)
add_library(modules::perception::common::geometry::camera_homography  ALIAS   modules_perception_common_geometry_camera_homography)

