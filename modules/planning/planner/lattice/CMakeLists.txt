cmake_minimum_required(VERSION 3.16)

project(modules_planning_planner_lattice)
message("${Green} [info] modules_planning_planner_lattice cmakelist ${ColourReset}")

add_library(modules_planning_planner_lattice_lattice_planner  SHARED
  lattice_planner.cc
)
set_target_properties(modules_planning_planner_lattice_lattice_planner  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_planner_lattice_lattice_planner
  cyber::common::log
  modules::common::math::path_matcher
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::common::planning_gflags
  modules::planning::constraint_checker::constraint_checker
  modules::planning::constraint_checker::collision_checker
  modules::planning::lattice::behavior::path_time_graph
  modules::planning::lattice::trajectory_generation::backup_trajectory_generator
  modules::planning::lattice::trajectory_generation::lattice_trajectory1d
  modules::planning::lattice::trajectory_generation::trajectory1d_generator
  modules::planning::lattice::trajectory_generation::trajectory_combiner
  modules::planning::lattice::trajectory_generation::trajectory_evaluator
  modules::planning::planner::planner
  modules::planning::proto::planning_cc_proto
)
add_library(modules::planning::planner::lattice::lattice_planner  ALIAS   modules_planning_planner_lattice_lattice_planner)

