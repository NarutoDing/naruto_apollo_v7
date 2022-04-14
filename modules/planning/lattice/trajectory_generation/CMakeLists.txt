cmake_minimum_required(VERSION 3.16)

project(modules_planning_lattice_trajectory_generation)
message("${Green} [info] modules_planning_lattice_trajectory_generation cmakelist ${ColourReset}")

add_library(modules_planning_lattice_trajectory_generation_lattice_trajectory1d  SHARED
  lattice_trajectory1d.cc
)
set_target_properties(modules_planning_lattice_trajectory_generation_lattice_trajectory1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_trajectory_generation_lattice_trajectory1d
  cyber::common::log
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::lattice::trajectory_generation::lattice_trajectory1d  ALIAS   modules_planning_lattice_trajectory_generation_lattice_trajectory1d)

add_library(modules_planning_lattice_trajectory_generation_end_condition_sampler  SHARED
  end_condition_sampler.cc
)
set_target_properties(modules_planning_lattice_trajectory_generation_end_condition_sampler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_trajectory_generation_end_condition_sampler
  modules::common::configs::vehicle_config_helper
  modules::planning::common::planning_gflags
  modules::planning::lattice::behavior::feasible_region
  modules::planning::lattice::behavior::path_time_graph
  modules::planning::lattice::behavior::prediction_querier
  modules::planning::proto::lattice_structure_cc_proto
)
add_library(modules::planning::lattice::trajectory_generation::end_condition_sampler  ALIAS   modules_planning_lattice_trajectory_generation_end_condition_sampler)

add_library(modules_planning_lattice_trajectory_generation_trajectory1d_generator  SHARED
  trajectory1d_generator.cc
)
set_target_properties(modules_planning_lattice_trajectory_generation_trajectory1d_generator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_trajectory_generation_trajectory1d_generator
  modules::planning::lattice::trajectory_generation::end_condition_sampler
  modules::planning::lattice::trajectory_generation::lateral_osqp_optimizer
  modules::planning::lattice::trajectory_generation::lateral_qp_optimizer
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory1d::constant_deceleration_trajectory1d
  modules::planning::common::trajectory1d::piecewise_acceleration_trajectory1d
  modules::planning::common::trajectory1d::piecewise_trajectory1d
  modules::planning::common::trajectory1d::standing_still_trajectory1d
  modules::planning::lattice::behavior::path_time_graph
  modules::planning::lattice::behavior::prediction_querier
  modules::planning::lattice::trajectory_generation::lattice_trajectory1d
  modules::planning::math::curve1d::quartic_polynomial_curve1d
  modules::planning::math::curve1d::quintic_polynomial_curve1d
  modules::planning::proto::lattice_structure_cc_proto
)
add_library(modules::planning::lattice::trajectory_generation::trajectory1d_generator  ALIAS   modules_planning_lattice_trajectory_generation_trajectory1d_generator)

add_library(modules_planning_lattice_trajectory_generation_trajectory_evaluator  SHARED
  trajectory_evaluator.cc
)
set_target_properties(modules_planning_lattice_trajectory_generation_trajectory_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_trajectory_generation_trajectory_evaluator
  modules::common::math::path_matcher
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory1d::piecewise_acceleration_trajectory1d
  modules::planning::constraint_checker::constraint_checker1d
  modules::planning::lattice::behavior::path_time_graph
  modules::planning::lattice::trajectory_generation::piecewise_braking_trajectory_generator
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::lattice::trajectory_generation::trajectory_evaluator  ALIAS   modules_planning_lattice_trajectory_generation_trajectory_evaluator)

add_library(modules_planning_lattice_trajectory_generation_backup_trajectory_generator  SHARED
  backup_trajectory_generator.cc
)
set_target_properties(modules_planning_lattice_trajectory_generation_backup_trajectory_generator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_trajectory_generation_backup_trajectory_generator
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::common::trajectory1d::constant_deceleration_trajectory1d
  modules::planning::constraint_checker::collision_checker
  modules::planning::lattice::trajectory_generation::trajectory1d_generator
  modules::planning::lattice::trajectory_generation::trajectory_combiner
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::lattice::trajectory_generation::backup_trajectory_generator  ALIAS   modules_planning_lattice_trajectory_generation_backup_trajectory_generator)

add_library(modules_planning_lattice_trajectory_generation_trajectory_combiner  SHARED
  trajectory_combiner.cc
)
set_target_properties(modules_planning_lattice_trajectory_generation_trajectory_combiner  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_trajectory_generation_trajectory_combiner
  modules::common::math::cartesian_frenet_conversion
  modules::common::math::path_matcher
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::lattice::trajectory_generation::trajectory_combiner  ALIAS   modules_planning_lattice_trajectory_generation_trajectory_combiner)

add_library(modules_planning_lattice_trajectory_generation_piecewise_braking_trajectory_generator  SHARED
  piecewise_braking_trajectory_generator.cc
)
set_target_properties(modules_planning_lattice_trajectory_generation_piecewise_braking_trajectory_generator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_trajectory_generation_piecewise_braking_trajectory_generator
  modules::planning::common::trajectory1d::piecewise_acceleration_trajectory1d
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::lattice::trajectory_generation::piecewise_braking_trajectory_generator  ALIAS   modules_planning_lattice_trajectory_generation_piecewise_braking_trajectory_generator)

add_library(modules_planning_lattice_trajectory_generation_lateral_qp_optimizer  SHARED
  lateral_qp_optimizer.cc
)
set_target_properties(modules_planning_lattice_trajectory_generation_lateral_qp_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_trajectory_generation_lateral_qp_optimizer
  modules::common::util::util
  modules::planning::common::trajectory1d::piecewise_jerk_trajectory1d
)
add_library(modules::planning::lattice::trajectory_generation::lateral_qp_optimizer  ALIAS   modules_planning_lattice_trajectory_generation_lateral_qp_optimizer)

add_library(modules_planning_lattice_trajectory_generation_lateral_osqp_optimizer  SHARED
  lateral_osqp_optimizer.cc
)
set_target_properties(modules_planning_lattice_trajectory_generation_lateral_osqp_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_lattice_trajectory_generation_lateral_osqp_optimizer
  modules::planning::lattice::trajectory_generation::lateral_qp_optimizer
  cyber::common::log
  modules::common::math::matrix_operations
  modules::planning::common::trajectory1d::piecewise_jerk_trajectory1d
  ${eigen}
  ${osqp}
)
add_library(modules::planning::lattice::trajectory_generation::lateral_osqp_optimizer  ALIAS   modules_planning_lattice_trajectory_generation_lateral_osqp_optimizer)

