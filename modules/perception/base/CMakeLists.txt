cmake_minimum_required(VERSION 3.16)

project(modules_perception_base)
message("${Green} [info] modules_perception_base cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_base  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_base_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_base
  modules::perception::base::base_type
  modules::perception::base::blob
  modules::perception::base::box
  modules::perception::base::camera
  modules::perception::base::common
  modules::perception::base::distortion_model
  modules::perception::base::frame
  modules::perception::base::image
  modules::perception::base::impending_collision_edge
  modules::perception::base::object
  modules::perception::base::object_pool
  modules::perception::base::object_pool_types
  modules::perception::base::omnidirectional_model
  modules::perception::base::point_cloud
  modules::perception::base::point_cloud_util
  modules::perception::base::polynomial
  modules::perception::base::syncedmem
  modules::perception::base::traffic_light
)
add_library(modules::perception::base::base  ALIAS   modules_perception_base_base)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_base_type  SHARED
  ${virtual_cc}
  hdmap_struct.h
  landmark_struct.h
  lane_struct.h
  sensor_meta.h
  vehicle_struct.h
)
set_target_properties(modules_perception_base_base_type  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_base_type
  modules::common::util::eigen_defs
)
add_library(modules::perception::base::base_type  ALIAS   modules_perception_base_base_type)

add_library(modules_perception_base_blob  SHARED
  blob.cc
)
set_target_properties(modules_perception_base_blob  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_blob
  modules::perception::base::common
  modules::perception::base::syncedmem
  cyber::cyber
  ${absl}
  ${cuda}
)
add_library(modules::perception::base::blob  ALIAS   modules_perception_base_blob)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_box  SHARED
  ${virtual_cc}
  box.h
  comparison_traits.h
)
set_target_properties(modules_perception_base_box  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_box
  modules::perception::base::point_cloud
)
add_library(modules::perception::base::box  ALIAS   modules_perception_base_box)

add_library(modules_perception_base_camera  SHARED
  camera.cc
)
set_target_properties(modules_perception_base_camera  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_camera
  ${eigen}
)
add_library(modules::perception::base::camera  ALIAS   modules_perception_base_camera)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_common  SHARED
  ${virtual_cc}
  common.h
)
set_target_properties(modules_perception_base_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_common
  ${cuda}
)
add_library(modules::perception::base::common  ALIAS   modules_perception_base_common)

add_library(modules_perception_base_distortion_model  SHARED
  distortion_model.cc
)
set_target_properties(modules_perception_base_distortion_model  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_distortion_model
  modules::perception::base::camera
  cyber::cyber
  ${eigen}
)
add_library(modules::perception::base::distortion_model  ALIAS   modules_perception_base_distortion_model)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_frame  SHARED
  ${virtual_cc}
  frame.h
  frame_supplement.h
)
set_target_properties(modules_perception_base_frame  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_frame
  modules::perception::base::base_type
  modules::perception::base::blob
  modules::perception::base::image
  modules::perception::base::impending_collision_edge
  ${eigen}
)
add_library(modules::perception::base::frame  ALIAS   modules_perception_base_frame)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_image  SHARED
  ${virtual_cc}
  image.h
  image_8u.h
)
set_target_properties(modules_perception_base_image  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_image
  modules::perception::base::base_type
  modules::perception::base::blob
)
add_library(modules::perception::base::image  ALIAS   modules_perception_base_image)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_impending_collision_edge  SHARED
  ${virtual_cc}
  impending_collision_edge.h
)
set_target_properties(modules_perception_base_impending_collision_edge  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_impending_collision_edge
  cyber::cyber
  ${eigen}
)
add_library(modules::perception::base::impending_collision_edge  ALIAS   modules_perception_base_impending_collision_edge)

add_library(modules_perception_base_object  SHARED
  object.cc
)
set_target_properties(modules_perception_base_object  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_object
  modules::perception::base::box
  modules::perception::base::point_cloud
  modules::common::proto::error_code_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::common::util::eigen_defs
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
  modules::map::proto::map_lane_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
  modules::prediction::proto::feature_cc_proto
  modules::prediction::proto::lane_graph_cc_proto
  modules::prediction::proto::prediction_point_cc_proto
  ${boost}
  ${eigen}
)
add_library(modules::perception::base::object  ALIAS   modules_perception_base_object)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_object_pool  SHARED
  ${virtual_cc}
  concurrent_object_pool.h
  light_object_pool.h
  object_pool.h
)
set_target_properties(modules_perception_base_object_pool  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_object_pool
  modules::perception::base::base_type
)
add_library(modules::perception::base::object_pool  ALIAS   modules_perception_base_object_pool)

add_library(modules_perception_base_object_pool_types  SHARED
  object_pool_types.cc
)
set_target_properties(modules_perception_base_object_pool_types  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_object_pool_types
  modules::perception::base::frame
  modules::perception::base::object
  modules::perception::base::object_pool
  modules::perception::base::point_cloud
  cyber::cyber
)
add_library(modules::perception::base::object_pool_types  ALIAS   modules_perception_base_object_pool_types)

add_library(modules_perception_base_omnidirectional_model  SHARED
  omnidirectional_model.cc
)
set_target_properties(modules_perception_base_omnidirectional_model  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_omnidirectional_model
  modules::perception::base::camera
  modules::perception::base::distortion_model
  modules::perception::base::polynomial
  cyber::cyber
  ${eigen}
)
add_library(modules::perception::base::omnidirectional_model  ALIAS   modules_perception_base_omnidirectional_model)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_point  SHARED
  ${virtual_cc}
  point.h
)
set_target_properties(modules_perception_base_point  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::base::point  ALIAS   modules_perception_base_point)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_point_cloud  SHARED
  ${virtual_cc}
  point_cloud.h
)
set_target_properties(modules_perception_base_point_cloud  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_point_cloud
  modules::perception::base::point
  modules::common::util::eigen_defs
  ${eigen}
)
add_library(modules::perception::base::point_cloud  ALIAS   modules_perception_base_point_cloud)

add_library(modules_perception_base_point_cloud_util  SHARED
  point_cloud_util.cc
)
set_target_properties(modules_perception_base_point_cloud_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_point_cloud_util
  modules::perception::base::point_cloud
  cyber::cyber
  ${eigen}
  ${opencv}
)
add_library(modules::perception::base::point_cloud_util  ALIAS   modules_perception_base_point_cloud_util)

add_library(modules_perception_base_polynomial  SHARED
  polynomial.cc
)
set_target_properties(modules_perception_base_polynomial  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::base::polynomial  ALIAS   modules_perception_base_polynomial)

add_library(modules_perception_base_syncedmem  SHARED
  syncedmem.cc
)
set_target_properties(modules_perception_base_syncedmem  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_syncedmem
  modules::perception::base::common
  cyber::cyber
  ${cuda}
)
add_library(modules::perception::base::syncedmem  ALIAS   modules_perception_base_syncedmem)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_traffic_light  SHARED
  ${virtual_cc}
  traffic_light.h
)
set_target_properties(modules_perception_base_traffic_light  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_traffic_light
  modules::perception::base::box
)
add_library(modules::perception::base::traffic_light  ALIAS   modules_perception_base_traffic_light)

