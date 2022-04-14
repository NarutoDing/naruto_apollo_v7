cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_data_association_hm_data_association)
message("${Green} [info] modules_perception_fusion_lib_data_association_hm_data_association cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_fusion_lib_data_association_hm_data_association_chi_squared_cdf  SHARED
  ${virtual_cc}
  chi_squared_cdf_1_0.0500_0.999900.h
  chi_squared_cdf_2_0.0500_0.999900.h
)
set_target_properties(modules_perception_fusion_lib_data_association_hm_data_association_chi_squared_cdf  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::fusion::lib::data_association::hm_data_association::chi_squared_cdf  ALIAS   modules_perception_fusion_lib_data_association_hm_data_association_chi_squared_cdf)

add_library(modules_perception_fusion_lib_data_association_hm_data_association_hm_tracks_objects_match  SHARED
  hm_tracks_objects_match.cc
)
set_target_properties(modules_perception_fusion_lib_data_association_hm_data_association_hm_tracks_objects_match  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_data_association_hm_data_association_hm_tracks_objects_match
  modules::perception::fusion::lib::data_association::hm_data_association::track_object_distance
  modules::perception::common::graph::gated_hungarian_bigraph_matcher
  modules::perception::common::graph::secure_matrix
  modules::perception::fusion::base::scene
  modules::perception::fusion::lib::interface::interface
)
add_library(modules::perception::fusion::lib::data_association::hm_data_association::hm_tracks_objects_match  ALIAS   modules_perception_fusion_lib_data_association_hm_data_association_hm_tracks_objects_match)

add_library(modules_perception_fusion_lib_data_association_hm_data_association_probabilities  SHARED
  probabilities.cc
)
set_target_properties(modules_perception_fusion_lib_data_association_hm_data_association_probabilities  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::fusion::lib::data_association::hm_data_association::probabilities  ALIAS   modules_perception_fusion_lib_data_association_hm_data_association_probabilities)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_fusion_lib_data_association_hm_data_association_projection_cache  SHARED
  ${virtual_cc}
  projection_cache.h
)
set_target_properties(modules_perception_fusion_lib_data_association_hm_data_association_projection_cache  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_data_association_hm_data_association_projection_cache
  modules::common::math::math_utils
)
add_library(modules::perception::fusion::lib::data_association::hm_data_association::projection_cache  ALIAS   modules_perception_fusion_lib_data_association_hm_data_association_projection_cache)

add_library(modules_perception_fusion_lib_data_association_hm_data_association_track_object_distance  SHARED
  track_object_distance.cc
)
set_target_properties(modules_perception_fusion_lib_data_association_hm_data_association_track_object_distance  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_data_association_hm_data_association_track_object_distance
  modules::perception::fusion::lib::data_association::hm_data_association::chi_squared_cdf
  modules::perception::fusion::lib::data_association::hm_data_association::probabilities
  modules::perception::fusion::lib::data_association::hm_data_association::projection_cache
  modules::perception::fusion::lib::data_association::hm_data_association::track_object_similarity
  modules::perception::base::base_type
  modules::perception::base::camera
  modules::perception::base::point_cloud
  modules::perception::common::geometry::camera_homography
  modules::perception::common::sensor_manager::sensor_manager
  modules::perception::fusion::base::fusion_log
  modules::perception::fusion::base::sensor
  modules::perception::fusion::base::sensor_data_manager
  modules::perception::fusion::base::track
  modules::perception::fusion::common::camera_util
)
add_library(modules::perception::fusion::lib::data_association::hm_data_association::track_object_distance  ALIAS   modules_perception_fusion_lib_data_association_hm_data_association_track_object_distance)

add_library(modules_perception_fusion_lib_data_association_hm_data_association_track_object_similarity  SHARED
  track_object_similarity.cc
)
set_target_properties(modules_perception_fusion_lib_data_association_hm_data_association_track_object_similarity  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_data_association_hm_data_association_track_object_similarity
  modules::perception::fusion::lib::data_association::hm_data_association::chi_squared_cdf
  modules::perception::fusion::lib::data_association::hm_data_association::probabilities
  modules::perception::fusion::lib::data_association::hm_data_association::projection_cache
  modules::perception::fusion::base::fusion_log
  modules::perception::fusion::base::sensor
  modules::perception::fusion::common::camera_util
)
add_library(modules::perception::fusion::lib::data_association::hm_data_association::track_object_similarity  ALIAS   modules_perception_fusion_lib_data_association_hm_data_association_track_object_similarity)

