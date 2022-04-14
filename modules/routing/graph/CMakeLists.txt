cmake_minimum_required(VERSION 3.16)

project(modules_routing_graph)
message("${Green} [info] modules_routing_graph cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_routing_graph_graph  SHARED
  ${virtual_cc}
)
set_target_properties(modules_routing_graph_graph  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_graph_graph
  modules::routing::graph::routing_sub_topo_graph
  modules::routing::graph::routing_topo_graph
  modules::routing::graph::routing_topo_range_manager
)
add_library(modules::routing::graph::graph  ALIAS   modules_routing_graph_graph)

add_library(modules_routing_graph_routing_topo_range  SHARED
  topo_range.cc
)
set_target_properties(modules_routing_graph_routing_topo_range  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_graph_routing_topo_range
  modules::routing::common::routing_gflags
)
add_library(modules::routing::graph::routing_topo_range  ALIAS   modules_routing_graph_routing_topo_range)

add_library(modules_routing_graph_routing_topo_range_manager  SHARED
  topo_range_manager.cc
)
set_target_properties(modules_routing_graph_routing_topo_range_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_graph_routing_topo_range_manager
  modules::routing::graph::routing_topo_node
)
add_library(modules::routing::graph::routing_topo_range_manager  ALIAS   modules_routing_graph_routing_topo_range_manager)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_routing_graph_routing_range_utils  SHARED
  ${virtual_cc}
  range_utils.h
)
set_target_properties(modules_routing_graph_routing_range_utils  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::routing::graph::routing_range_utils  ALIAS   modules_routing_graph_routing_range_utils)

add_library(modules_routing_graph_routing_node_with_range  SHARED
  node_with_range.cc
)
set_target_properties(modules_routing_graph_routing_node_with_range  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_graph_routing_node_with_range
  modules::routing::graph::routing_topo_node
)
add_library(modules::routing::graph::routing_node_with_range  ALIAS   modules_routing_graph_routing_node_with_range)

add_library(modules_routing_graph_routing_topo_node  SHARED
  topo_node.cc
)
set_target_properties(modules_routing_graph_routing_topo_node  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_graph_routing_topo_node
  modules::routing::graph::routing_range_utils
  modules::routing::graph::routing_topo_range
  cyber::cyber
  modules::common::util::map_util
  modules::routing::proto::routing_cc_proto
  modules::routing::proto::topo_graph_cc_proto
)
add_library(modules::routing::graph::routing_topo_node  ALIAS   modules_routing_graph_routing_topo_node)

add_library(modules_routing_graph_routing_topo_graph  SHARED
  topo_graph.cc
)
set_target_properties(modules_routing_graph_routing_topo_graph  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_graph_routing_topo_graph
  modules::routing::graph::routing_topo_node
)
add_library(modules::routing::graph::routing_topo_graph  ALIAS   modules_routing_graph_routing_topo_graph)

add_library(modules_routing_graph_routing_sub_topo_graph  SHARED
  sub_topo_graph.cc
)
set_target_properties(modules_routing_graph_routing_sub_topo_graph  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_graph_routing_sub_topo_graph
  modules::routing::graph::routing_node_with_range
)
add_library(modules::routing::graph::routing_sub_topo_graph  ALIAS   modules_routing_graph_routing_sub_topo_graph)

add_library(modules_routing_graph_routing_topo_test_utils  SHARED
  topo_test_utils.cc
)
set_target_properties(modules_routing_graph_routing_topo_test_utils  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_graph_routing_topo_test_utils
  modules::routing::graph::routing_topo_graph
)
add_library(modules::routing::graph::routing_topo_test_utils  ALIAS   modules_routing_graph_routing_topo_test_utils)

