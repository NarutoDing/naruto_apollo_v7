cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_optimizers_path_time_heuristic)
message("${Green} [info] modules_planning_tasks_optimizers_path_time_heuristic cmakelist ${ColourReset}")

add_library(modules_planning_tasks_optimizers_path_time_heuristic_st_graph_point  SHARED
  st_graph_point.cc
)
set_target_properties(modules_planning_tasks_optimizers_path_time_heuristic_st_graph_point  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_path_time_heuristic_st_graph_point
  modules::planning::common::planning_gflags
  modules::planning::common::speed::st_point
)
add_library(modules::planning::tasks::optimizers::path_time_heuristic::st_graph_point  ALIAS   modules_planning_tasks_optimizers_path_time_heuristic_st_graph_point)

add_library(modules_planning_tasks_optimizers_path_time_heuristic_dp_st_cost  SHARED
  dp_st_cost.cc
)
set_target_properties(modules_planning_tasks_optimizers_path_time_heuristic_dp_st_cost  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_path_time_heuristic_dp_st_cost
  modules::planning::tasks::optimizers::path_time_heuristic::st_graph_point
  modules::common::proto::pnc_point_cc_proto
  modules::planning::common::frame
  modules::planning::common::obstacle
  modules::planning::common::speed::st_boundary
  modules::planning::tasks::utils::st_gap_estimator
)
add_library(modules::planning::tasks::optimizers::path_time_heuristic::dp_st_cost  ALIAS   modules_planning_tasks_optimizers_path_time_heuristic_dp_st_cost)

add_library(modules_planning_tasks_optimizers_path_time_heuristic_gridded_path_time_graph  SHARED
  gridded_path_time_graph.cc
)
set_target_properties(modules_planning_tasks_optimizers_path_time_heuristic_gridded_path_time_graph  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_path_time_heuristic_gridded_path_time_graph
  modules::planning::tasks::optimizers::path_time_heuristic::dp_st_cost
  modules::planning::tasks::optimizers::path_time_heuristic::st_graph_point
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::planning::common::obstacle
  modules::planning::common::path_decision
  modules::planning::common::st_graph_data
  modules::planning::common::speed::speed_data
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
)
add_library(modules::planning::tasks::optimizers::path_time_heuristic::gridded_path_time_graph  ALIAS   modules_planning_tasks_optimizers_path_time_heuristic_gridded_path_time_graph)

add_library(modules_planning_tasks_optimizers_path_time_heuristic_path_time_heuristic_optimizer  SHARED
  path_time_heuristic_optimizer.cc
)
set_target_properties(modules_planning_tasks_optimizers_path_time_heuristic_path_time_heuristic_optimizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_optimizers_path_time_heuristic_path_time_heuristic_optimizer
  modules::planning::tasks::optimizers::path_time_heuristic::dp_st_cost
  modules::planning::tasks::optimizers::path_time_heuristic::gridded_path_time_graph
  modules::common::configs::vehicle_config_helper
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::common::st_graph_data
  modules::planning::proto::planning_internal_cc_proto
  modules::planning::tasks::deciders::speed_bounds_decider::st_boundary_mapper
  modules::planning::tasks::optimizers::speed_optimizer
)
add_library(modules::planning::tasks::optimizers::path_time_heuristic::path_time_heuristic_optimizer  ALIAS   modules_planning_tasks_optimizers_path_time_heuristic_path_time_heuristic_optimizer)

