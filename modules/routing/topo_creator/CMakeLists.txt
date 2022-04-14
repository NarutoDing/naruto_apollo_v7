cmake_minimum_required(VERSION 3.16)

project(modules_routing_topo_creator)
message("${Green} [info] modules_routing_topo_creator cmakelist ${ColourReset}")

add_library(modules_routing_topo_creator_edge_creator  SHARED
  edge_creator.cc
)
set_target_properties(modules_routing_topo_creator_edge_creator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_topo_creator_edge_creator
  modules::routing::common::routing_gflags
  modules::routing::proto::routing_cc_proto
  modules::routing::proto::routing_config_cc_proto
  modules::routing::proto::topo_graph_cc_proto
)
add_library(modules::routing::topo_creator::edge_creator  ALIAS   modules_routing_topo_creator_edge_creator)

add_library(modules_routing_topo_creator_graph_creator  SHARED
  graph_creator.cc
)
set_target_properties(modules_routing_topo_creator_graph_creator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_topo_creator_graph_creator
  modules::routing::topo_creator::edge_creator
  modules::routing::topo_creator::node_creator
  modules::common::configs::vehicle_config_helper
  modules::map::hdmap::adapter::opendrive_adapter
)
add_library(modules::routing::topo_creator::graph_creator  ALIAS   modules_routing_topo_creator_graph_creator)

add_library(modules_routing_topo_creator_node_creator  SHARED
  node_creator.cc
)
set_target_properties(modules_routing_topo_creator_node_creator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_topo_creator_node_creator
  modules::map::proto::map_lane_cc_proto
  modules::routing::proto::routing_cc_proto
  modules::routing::proto::routing_config_cc_proto
  modules::routing::proto::topo_graph_cc_proto
)
add_library(modules::routing::topo_creator::node_creator  ALIAS   modules_routing_topo_creator_node_creator)

add_executable(topo_creator
  topo_creator.cc
)
target_link_libraries(topo_creator
  modules::routing::topo_creator::graph_creator
  modules::map::hdmap::hdmap_util
)
