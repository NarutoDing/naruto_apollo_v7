cmake_minimum_required(VERSION 3.16)

project(modules_planning_constraint_checker)
message("${Green} [info] modules_planning_constraint_checker cmakelist ${ColourReset}")

add_library(modules_planning_constraint_checker_constraint_checker  SHARED
  constraint_checker.cc
)
set_target_properties(modules_planning_constraint_checker_constraint_checker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_constraint_checker_constraint_checker
  cyber::common::log
  modules::common::proto::pnc_point_cc_proto
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory::discretized_trajectory
)
add_library(modules::planning::constraint_checker::constraint_checker  ALIAS   modules_planning_constraint_checker_constraint_checker)

add_library(modules_planning_constraint_checker_constraint_checker1d  SHARED
  constraint_checker1d.cc
)
set_target_properties(modules_planning_constraint_checker_constraint_checker1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_constraint_checker_constraint_checker1d
  cyber::common::log
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::constraint_checker::constraint_checker1d  ALIAS   modules_planning_constraint_checker_constraint_checker1d)

add_library(modules_planning_constraint_checker_collision_checker  SHARED
  collision_checker.cc
)
set_target_properties(modules_planning_constraint_checker_collision_checker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_constraint_checker_collision_checker
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::geometry
  modules::common::math::path_matcher
  modules::planning::common::frame
  modules::planning::common::obstacle
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::lattice::behavior::path_time_graph
  modules::planning::proto::st_drivable_boundary_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
)
add_library(modules::planning::constraint_checker::collision_checker  ALIAS   modules_planning_constraint_checker_collision_checker)

