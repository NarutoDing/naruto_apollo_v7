cmake_minimum_required(VERSION 3.16)

project(modules_planning_lattice_behavior)
message("${Green} [info] modules_planning_lattice_behavior cmakelist ${ColourReset}")

add_library(modules_planning_lattice_behavior_feasible_region  SHARED
  feasible_region.cc
)
set_target_properties(modules_planning_lattice_behavior_feasible_region  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_behavior_feasible_region
  cyber::common::log
  modules::common::proto::pnc_point_cc_proto
  modules::planning::common::planning_gflags
)
add_library(modules::planning::lattice::behavior::feasible_region  ALIAS   modules_planning_lattice_behavior_feasible_region)

add_library(modules_planning_lattice_behavior_path_time_graph  SHARED
  path_time_graph.cc
)
set_target_properties(modules_planning_lattice_behavior_path_time_graph  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_behavior_path_time_graph
  cyber::common::log
  modules::common::math::linear_interpolation
  modules::common::math::path_matcher
  modules::common::proto::pnc_point_cc_proto
  modules::planning::common::frame
  modules::planning::common::obstacle
  modules::planning::common::planning_gflags
  modules::planning::proto::lattice_structure_cc_proto
  modules::planning::reference_line::reference_line
)
add_library(modules::planning::lattice::behavior::path_time_graph  ALIAS   modules_planning_lattice_behavior_path_time_graph)

add_library(modules_planning_lattice_behavior_prediction_querier  SHARED
  prediction_querier.cc
)
set_target_properties(modules_planning_lattice_behavior_prediction_querier  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_behavior_prediction_querier
  modules::common::math::math
  modules::common::math::path_matcher
  modules::planning::common::obstacle
  modules::planning::proto::lattice_structure_cc_proto
  modules::planning::proto::planning_cc_proto
)
add_library(modules::planning::lattice::behavior::prediction_querier  ALIAS   modules_planning_lattice_behavior_prediction_querier)

