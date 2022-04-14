cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_speed_bounds_decider)
message("${Green} [info] modules_planning_tasks_deciders_speed_bounds_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_speed_bounds_decider_speed_bounds_decider  SHARED
  speed_bounds_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_speed_bounds_decider_speed_bounds_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_speed_bounds_decider_speed_bounds_decider
  modules::planning::tasks::deciders::speed_bounds_decider::st_boundary_mapper
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::common::st_graph_data
  modules::planning::common::util::common_lib
  modules::planning::tasks::task
  modules::planning::tasks::deciders::decider_base
  modules::planning::tasks::deciders::lane_change_decider::lane_change_decider
)
add_library(modules::planning::tasks::deciders::speed_bounds_decider::speed_bounds_decider  ALIAS   modules_planning_tasks_deciders_speed_bounds_decider_speed_bounds_decider)

add_library(modules_planning_tasks_deciders_speed_bounds_decider_st_boundary_mapper  SHARED
  speed_limit_decider.cc
  st_boundary_mapper.cc
)
set_target_properties(modules_planning_tasks_deciders_speed_bounds_decider_st_boundary_mapper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_speed_bounds_decider_st_boundary_mapper
  modules::common::configs::vehicle_config_helper
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::map::pnc_map::pnc_map
  modules::planning::common::dependency_injector
  modules::planning::common::frame
  modules::planning::common::obstacle
  modules::planning::common::path_decision
  modules::planning::common::planning_gflags
  modules::planning::common::speed_limit
  modules::planning::common::path::discretized_path
  modules::planning::common::path::frenet_frame_path
  modules::planning::common::path::path_data
  modules::planning::common::speed::st_boundary
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::reference_line::reference_line
)
add_library(modules::planning::tasks::deciders::speed_bounds_decider::st_boundary_mapper  ALIAS   modules_planning_tasks_deciders_speed_bounds_decider_st_boundary_mapper)

