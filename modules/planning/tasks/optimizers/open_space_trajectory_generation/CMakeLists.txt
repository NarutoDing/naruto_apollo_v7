cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_optimizers_open_space_trajectory_generation)
message("${Green} [info] modules_planning_tasks_optimizers_open_space_trajectory_generation cmakelist ${ColourReset}")

add_library(modules_planning_tasks_optimizers_open_space_trajectory_generation_open_space_trajectory_provider  SHARED
  open_space_trajectory_provider.cc
)
set_target_properties(modules_planning_tasks_optimizers_open_space_trajectory_generation_open_space_trajectory_provider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_open_space_trajectory_generation_open_space_trajectory_provider
  modules::planning::tasks::optimizers::open_space_trajectory_generation::open_space_trajectory_optimizer
  modules::common::status::status
  modules::planning::common::planning_common
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory_stitcher
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::tasks::task
  modules::planning::tasks::optimizers::trajectory_optimizer
  
  ${cuda}
)
add_library(modules::planning::tasks::optimizers::open_space_trajectory_generation::open_space_trajectory_provider  ALIAS   modules_planning_tasks_optimizers_open_space_trajectory_generation_open_space_trajectory_provider)

add_library(modules_planning_tasks_optimizers_open_space_trajectory_generation_open_space_trajectory_optimizer  SHARED
  open_space_trajectory_optimizer.cc
)
set_target_properties(modules_planning_tasks_optimizers_open_space_trajectory_generation_open_space_trajectory_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_open_space_trajectory_generation_open_space_trajectory_optimizer
  cyber::common::log
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::common::util::util
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::common::frame
  modules::planning::open_space::coarse_trajectory_generator::hybrid_a_star
  modules::planning::open_space::trajectory_smoother::distance_approach_problem
  modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_problem
  modules::planning::open_space::trajectory_smoother::iterative_anchoring_smoother
  modules::planning::proto::planning_config_cc_proto
  ${gflags_LIBRARIES}
  ${eigen}
)
add_library(modules::planning::tasks::optimizers::open_space_trajectory_generation::open_space_trajectory_optimizer  ALIAS   modules_planning_tasks_optimizers_open_space_trajectory_generation_open_space_trajectory_optimizer)

