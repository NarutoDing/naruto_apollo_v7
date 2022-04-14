cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_optimizers)
message("${Green} [info] modules_planning_tasks_optimizers cmakelist ${ColourReset}")

add_library(modules_planning_tasks_optimizers_path_optimizer  SHARED
  path_optimizer.cc
)
set_target_properties(modules_planning_tasks_optimizers_path_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_path_optimizer
  modules::common::status::status
  modules::planning::common::path_decision
  modules::planning::common::reference_line_info
  modules::planning::common::path::path_data
  modules::planning::common::speed::speed_data
  modules::planning::tasks::task
  ${eigen}
)
add_library(modules::planning::tasks::optimizers::path_optimizer  ALIAS   modules_planning_tasks_optimizers_path_optimizer)

add_library(modules_planning_tasks_optimizers_speed_optimizer  SHARED
  speed_optimizer.cc
)
set_target_properties(modules_planning_tasks_optimizers_speed_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_speed_optimizer
  modules::common::status::status
  modules::planning::common::path_decision
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::common::speed_limit
  modules::planning::common::st_graph_data
  modules::planning::common::path::path_data
  modules::planning::common::speed::speed_data
  modules::planning::tasks::task
  ${eigen}
)
add_library(modules::planning::tasks::optimizers::speed_optimizer  ALIAS   modules_planning_tasks_optimizers_speed_optimizer)

add_library(modules_planning_tasks_optimizers_trajectory_optimizer  SHARED
  trajectory_optimizer.cc
)
set_target_properties(modules_planning_tasks_optimizers_trajectory_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_trajectory_optimizer
  modules::common::status::status
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::tasks::task
)
add_library(modules::planning::tasks::optimizers::trajectory_optimizer  ALIAS   modules_planning_tasks_optimizers_trajectory_optimizer)

