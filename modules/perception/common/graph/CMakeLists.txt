cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_graph)
message("${Green} [info] modules_perception_common_graph cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_graph_graph  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_common_graph_graph  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_graph_graph
  modules::perception::common::graph::conditional_clustering
  modules::perception::common::graph::connected_component_analysis
  modules::perception::common::graph::disjoint_set
  modules::perception::common::graph::gated_hungarian_bigraph_matcher
  modules::perception::common::graph::graph_segmentor
  modules::perception::common::graph::hungarian_optimizer
  modules::perception::common::graph::secure_matrix
)
add_library(modules::perception::common::graph::graph  ALIAS   modules_perception_common_graph_graph)

add_library(modules_perception_common_graph_disjoint_set  SHARED
  disjoint_set.cc
)
set_target_properties(modules_perception_common_graph_disjoint_set  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::common::graph::disjoint_set  ALIAS   modules_perception_common_graph_disjoint_set)

add_library(modules_perception_common_graph_graph_segmentor  SHARED
  graph_segmentor.cc
)
set_target_properties(modules_perception_common_graph_graph_segmentor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_graph_graph_segmentor
  modules::perception::common::graph::disjoint_set
  cyber::cyber
)
add_library(modules::perception::common::graph::graph_segmentor  ALIAS   modules_perception_common_graph_graph_segmentor)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_graph_secure_matrix  SHARED
  ${virtual_cc}
  secure_matrix.h
)
set_target_properties(modules_perception_common_graph_secure_matrix  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_graph_secure_matrix
  ${eigen}
)
add_library(modules::perception::common::graph::secure_matrix  ALIAS   modules_perception_common_graph_secure_matrix)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_graph_hungarian_optimizer  SHARED
  ${virtual_cc}
  hungarian_optimizer.h
)
set_target_properties(modules_perception_common_graph_hungarian_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_graph_hungarian_optimizer
  ${eigen}
)
add_library(modules::perception::common::graph::hungarian_optimizer  ALIAS   modules_perception_common_graph_hungarian_optimizer)

add_library(modules_perception_common_graph_connected_component_analysis  SHARED
  connected_component_analysis.cc
)
set_target_properties(modules_perception_common_graph_connected_component_analysis  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_graph_connected_component_analysis
  cyber::cyber
)
add_library(modules::perception::common::graph::connected_component_analysis  ALIAS   modules_perception_common_graph_connected_component_analysis)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_graph_conditional_clustering  SHARED
  ${virtual_cc}
  conditional_clustering.h
)
set_target_properties(modules_perception_common_graph_conditional_clustering  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_graph_conditional_clustering
  modules::perception::base::point_cloud
  modules::perception::common::geometry::basic
  ${eigen}
)
add_library(modules::perception::common::graph::conditional_clustering  ALIAS   modules_perception_common_graph_conditional_clustering)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_graph_gated_hungarian_bigraph_matcher  SHARED
  ${virtual_cc}
  gated_hungarian_bigraph_matcher.h
)
set_target_properties(modules_perception_common_graph_gated_hungarian_bigraph_matcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_graph_gated_hungarian_bigraph_matcher
  modules::perception::common::graph::connected_component_analysis
  modules::perception::common::graph::hungarian_optimizer
  modules::perception::common::graph::secure_matrix
  cyber::cyber
)
add_library(modules::perception::common::graph::gated_hungarian_bigraph_matcher  ALIAS   modules_perception_common_graph_gated_hungarian_bigraph_matcher)

