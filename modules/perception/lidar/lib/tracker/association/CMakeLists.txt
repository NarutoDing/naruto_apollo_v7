cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_tracker_association)
message("${Green} [info] modules_perception_lidar_lib_tracker_association cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_tracker_association_multi_hm_bipartite_graph_matcher  SHARED
  multi_hm_bipartite_graph_matcher.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_association_multi_hm_bipartite_graph_matcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_association_multi_hm_bipartite_graph_matcher
  cyber::cyber
  modules::perception::common::graph::gated_hungarian_bigraph_matcher
  modules::perception::common::graph::secure_matrix
  modules::perception::lidar::lib::interface::base_bipartite_graph_matcher
  ${eigen}
  
)
add_library(modules::perception::lidar::lib::tracker::association::multi_hm_bipartite_graph_matcher  ALIAS   modules_perception_lidar_lib_tracker_association_multi_hm_bipartite_graph_matcher)

add_library(modules_perception_lidar_lib_tracker_association_gnn_bipartite_graph_matcher  SHARED
  gnn_bipartite_graph_matcher.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_association_gnn_bipartite_graph_matcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_association_gnn_bipartite_graph_matcher
  cyber::cyber
  modules::perception::common::graph::gated_hungarian_bigraph_matcher
  modules::perception::common::graph::secure_matrix
  modules::perception::lidar::lib::interface::base_bipartite_graph_matcher
  
)
add_library(modules::perception::lidar::lib::tracker::association::gnn_bipartite_graph_matcher  ALIAS   modules_perception_lidar_lib_tracker_association_gnn_bipartite_graph_matcher)

add_library(modules_perception_lidar_lib_tracker_association_distance_collection  SHARED
  distance_collection.cc
)
set_target_properties(modules_perception_lidar_lib_tracker_association_distance_collection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_tracker_association_distance_collection
  modules::common::math::geometry
  modules::perception::common::geometry::basic
  modules::perception::common::geometry::common
  modules::perception::lidar::common::lidar_log
  modules::perception::lidar::lib::tracker::common::mlf_track_data_with_track_pool_types
  modules::perception::lidar::lib::tracker::common::track_data
  modules::perception::lidar::lib::tracker::common::tracked_object
  
)
add_library(modules::perception::lidar::lib::tracker::association::distance_collection  ALIAS   modules_perception_lidar_lib_tracker_association_distance_collection)

