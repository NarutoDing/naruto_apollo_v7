cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks)
message("${Green} [info] modules_planning_tasks cmakelist ${ColourReset}")

add_library(modules_planning_tasks_task  SHARED
  task.cc
)
set_target_properties(modules_planning_tasks_task  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_task
  modules::common::status::status
  modules::planning::common::dependency_injector
  modules::planning::common::frame
  modules::planning::common::reference_line_info
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::common::trajectory::publishable_trajectory
  modules::planning::proto::planning_config_cc_proto
)
add_library(modules::planning::tasks::task  ALIAS   modules_planning_tasks_task)

add_library(modules_planning_tasks_task_factory  SHARED
  task_factory.cc
)
set_target_properties(modules_planning_tasks_task_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_task_factory
  modules::planning::tasks::task
  modules::planning::proto::planning_config_cc_proto
  modules::planning::tasks::deciders::creep_decider::creep_decider
  modules::planning::tasks::deciders::lane_change_decider::lane_change_decider
  modules::planning::tasks::deciders::open_space_decider::open_space_fallback_decider
  modules::planning::tasks::deciders::open_space_decider::open_space_pre_stop_decider
  modules::planning::tasks::deciders::open_space_decider::open_space_roi_decider
  modules::planning::tasks::deciders::path_assessment_decider::path_assessment_decider
  modules::planning::tasks::deciders::path_bounds_decider::path_bounds_decider
  modules::planning::tasks::deciders::path_decider::path_decider
  modules::planning::tasks::deciders::path_lane_borrow_decider::path_lane_borrow_decider
  modules::planning::tasks::deciders::path_reference_decider::path_reference_decider
  modules::planning::tasks::deciders::path_reuse_decider::path_reuse_decider
  modules::planning::tasks::deciders::rss_decider::rss_decider
  modules::planning::tasks::deciders::rule_based_stop_decider::rule_based_stop_decider
  modules::planning::tasks::deciders::speed_bounds_decider::speed_bounds_decider
  modules::planning::tasks::deciders::speed_decider::speed_decider
  modules::planning::tasks::deciders::st_bounds_decider::st_bounds_decider
  modules::planning::tasks::learning_model::learning_model_inference_task
  modules::planning::tasks::learning_model::learning_model_inference_trajectory_task
  modules::planning::tasks::optimizers::open_space_trajectory_generation::open_space_trajectory_provider
  modules::planning::tasks::optimizers::open_space_trajectory_partition::open_space_trajectory_partition
  modules::planning::tasks::optimizers::path_time_heuristic::path_time_heuristic_optimizer
  modules::planning::tasks::optimizers::piecewise_jerk_path::piecewise_jerk_path_optimizer
  modules::planning::tasks::optimizers::piecewise_jerk_speed::piecewise_jerk_speed_nonlinear_optimizer
  modules::planning::tasks::optimizers::piecewise_jerk_speed::piecewise_jerk_speed_optimizer
)
add_library(modules::planning::tasks::task_factory  ALIAS   modules_planning_tasks_task_factory)

