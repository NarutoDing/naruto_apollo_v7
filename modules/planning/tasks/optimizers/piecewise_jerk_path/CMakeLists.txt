cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_optimizers_piecewise_jerk_path)
message("${Green} [info] modules_planning_tasks_optimizers_piecewise_jerk_path cmakelist ${ColourReset}")

add_library(modules_planning_tasks_optimizers_piecewise_jerk_path_piecewise_jerk_path_optimizer  SHARED
  piecewise_jerk_path_optimizer.cc
)
set_target_properties(modules_planning_tasks_optimizers_piecewise_jerk_path_piecewise_jerk_path_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_piecewise_jerk_path_piecewise_jerk_path_optimizer
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::math::cartesian_frenet_conversion
  modules::common::math::qp_solver::qp_solver
  modules::common::proto::pnc_point_cc_proto
  modules::common::util::util
  modules::planning::common::obstacle
  modules::planning::common::path_boundary
  modules::planning::common::path_decision
  modules::planning::common::planning_context
  modules::planning::common::planning_gflags
  modules::planning::common::path::discretized_path
  modules::planning::common::path::frenet_frame_path
  modules::planning::common::path::path_data
  modules::planning::common::speed::speed_data
  modules::planning::lattice::trajectory_generation::trajectory1d_generator
  modules::planning::math::polynomial_xd
  modules::planning::math::curve1d::polynomial_curve1d
  modules::planning::math::curve1d::quintic_polynomial_curve1d
  modules::planning::math::piecewise_jerk::piecewise_jerk_path_problem
  modules::planning::proto::planning_cc_proto
  modules::planning::reference_line::reference_line
  modules::planning::tasks::optimizers::path_optimizer
  ${eigen}
)
add_library(modules::planning::tasks::optimizers::piecewise_jerk_path::piecewise_jerk_path_optimizer  ALIAS   modules_planning_tasks_optimizers_piecewise_jerk_path_piecewise_jerk_path_optimizer)

add_library(modules_planning_tasks_optimizers_piecewise_jerk_path_piecewise_jerk_path_ipopt_solver  SHARED
  piecewise_jerk_path_ipopt_solver.cc
)
set_target_properties(modules_planning_tasks_optimizers_piecewise_jerk_path_piecewise_jerk_path_ipopt_solver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_piecewise_jerk_path_piecewise_jerk_path_ipopt_solver
  cyber::cyber
  ${eigen}
  ${ipopt}
)
add_library(modules::planning::tasks::optimizers::piecewise_jerk_path::piecewise_jerk_path_ipopt_solver  ALIAS   modules_planning_tasks_optimizers_piecewise_jerk_path_piecewise_jerk_path_ipopt_solver)

