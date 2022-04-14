cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_optimizers_piecewise_jerk_speed)
message("${Green} [info] modules_planning_tasks_optimizers_piecewise_jerk_speed cmakelist ${ColourReset}")

add_library(modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_optimizer  SHARED
  piecewise_jerk_speed_optimizer.cc
)
set_target_properties(modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_optimizer
  modules::common::proto::error_code_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::planning::common::speed_profile_generator
  modules::planning::common::st_graph_data
  modules::planning::math::piecewise_jerk::piecewise_jerk_speed_problem
  modules::planning::tasks::optimizers::speed_optimizer
)
add_library(modules::planning::tasks::optimizers::piecewise_jerk_speed::piecewise_jerk_speed_optimizer  ALIAS   modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_optimizer)

add_library(modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_nonlinear_optimizer  SHARED
  piecewise_jerk_speed_nonlinear_optimizer.cc
)
set_target_properties(modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_nonlinear_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_nonlinear_optimizer
  modules::planning::tasks::optimizers::piecewise_jerk_speed::piecewise_jerk_speed_nonlinear_ipopt_interface
  modules::common::proto::error_code_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::common::util::util
  modules::planning::common::speed_profile_generator
  modules::planning::common::st_graph_data
  modules::planning::common::path::path_data
  modules::planning::common::trajectory1d::piecewise_jerk_trajectory1d
  modules::planning::math::piecewise_jerk::piecewise_jerk_path_problem
  modules::planning::math::piecewise_jerk::piecewise_jerk_speed_problem
  modules::planning::proto::ipopt_return_status_cc_proto
  modules::planning::tasks::optimizers::speed_optimizer
)
add_library(modules::planning::tasks::optimizers::piecewise_jerk_speed::piecewise_jerk_speed_nonlinear_optimizer  ALIAS   modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_nonlinear_optimizer)

add_library(modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_nonlinear_ipopt_interface  SHARED
  piecewise_jerk_speed_nonlinear_ipopt_interface.cc
)
set_target_properties(modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_nonlinear_ipopt_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_nonlinear_ipopt_interface
  modules::common::proto::pnc_point_cc_proto
  modules::planning::common::path::path_data
  modules::planning::common::trajectory1d::piecewise_jerk_trajectory1d
  ${ipopt}
)
add_library(modules::planning::tasks::optimizers::piecewise_jerk_speed::piecewise_jerk_speed_nonlinear_ipopt_interface  ALIAS   modules_planning_tasks_optimizers_piecewise_jerk_speed_piecewise_jerk_speed_nonlinear_ipopt_interface)

