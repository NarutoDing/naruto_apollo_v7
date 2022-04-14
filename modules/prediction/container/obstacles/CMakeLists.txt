cmake_minimum_required(VERSION 3.16)

project(modules_prediction_container_obstacles)
message("${Green} [info] modules_prediction_container_obstacles cmakelist ${ColourReset}")

add_library(modules_prediction_container_obstacles_obstacles_container  SHARED
  obstacles_container.cc
)
set_target_properties(modules_prediction_container_obstacles_obstacles_container  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_container_obstacles_obstacles_container
  modules::prediction::container::obstacles::obstacle_clusters
  modules::prediction::common::environment_features
  modules::prediction::common::feature_output
  modules::prediction::common::junction_analyzer
  modules::prediction::common::prediction_constants
  modules::prediction::container::container
  modules::prediction::container::obstacles::obstacle
  modules::prediction::proto::prediction_obstacle_cc_proto
  modules::prediction::submodules::submodule_output
)
add_library(modules::prediction::container::obstacles::obstacles_container  ALIAS   modules_prediction_container_obstacles_obstacles_container)

add_library(modules_prediction_container_obstacles_obstacle  SHARED
  obstacle.cc
)
set_target_properties(modules_prediction_container_obstacles_obstacle  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_container_obstacles_obstacle
  modules::prediction::container::obstacles::obstacle_clusters
  modules::common::filters::digital_filter
  modules::prediction::common::junction_analyzer
  modules::prediction::common::prediction_constants
  modules::prediction::network::rnn_model::rnn_model
  modules::prediction::proto::prediction_conf_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
)
add_library(modules::prediction::container::obstacles::obstacle  ALIAS   modules_prediction_container_obstacles_obstacle)

add_library(modules_prediction_container_obstacles_obstacle_clusters  SHARED
  obstacle_clusters.cc
)
set_target_properties(modules_prediction_container_obstacles_obstacle_clusters  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_container_obstacles_obstacle_clusters
  modules::common::util::util
  modules::prediction::common::road_graph
  modules::prediction::proto::feature_cc_proto
)
add_library(modules::prediction::container::obstacles::obstacle_clusters  ALIAS   modules_prediction_container_obstacles_obstacle_clusters)

