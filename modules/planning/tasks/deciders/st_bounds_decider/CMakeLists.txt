cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_st_bounds_decider)
message("${Green} [info] modules_planning_tasks_deciders_st_bounds_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_st_bounds_decider_st_bounds_decider  SHARED
  st_bounds_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_st_bounds_decider_st_bounds_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_st_bounds_decider_st_bounds_decider
  modules::planning::tasks::deciders::st_bounds_decider::st_driving_limits
  modules::planning::tasks::deciders::st_bounds_decider::st_guide_line
  modules::planning::tasks::deciders::st_bounds_decider::st_obstacles_processor
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::common::st_graph_data
  modules::planning::common::util::common_lib
  modules::planning::tasks::task
  modules::planning::tasks::deciders::decider_base
)
add_library(modules::planning::tasks::deciders::st_bounds_decider::st_bounds_decider  ALIAS   modules_planning_tasks_deciders_st_bounds_decider_st_bounds_decider)

add_library(modules_planning_tasks_deciders_st_bounds_decider_st_guide_line  SHARED
  st_guide_line.cc
)
set_target_properties(modules_planning_tasks_deciders_st_bounds_decider_st_guide_line  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_st_bounds_decider_st_guide_line
  modules::common::configs::vehicle_config_helper
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::map::pnc_map::pnc_map
  modules::map::proto::map_cc_proto
  modules::planning::common::frame
  modules::planning::common::obstacle
  modules::planning::common::path_decision
  modules::planning::common::planning_gflags
  modules::planning::common::speed_limit
  modules::planning::common::path::discretized_path
  modules::planning::common::path::frenet_frame_path
  modules::planning::common::path::path_data
  modules::planning::common::speed::speed_data
  modules::planning::common::speed::st_boundary
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::reference_line::reference_line
)
add_library(modules::planning::tasks::deciders::st_bounds_decider::st_guide_line  ALIAS   modules_planning_tasks_deciders_st_bounds_decider_st_guide_line)

add_library(modules_planning_tasks_deciders_st_bounds_decider_st_driving_limits  SHARED
  st_driving_limits.cc
)
set_target_properties(modules_planning_tasks_deciders_st_bounds_decider_st_driving_limits  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_st_bounds_decider_st_driving_limits
  modules::common::configs::vehicle_config_helper
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::status::status
  modules::map::pnc_map::pnc_map
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
  modules::planning::proto::planning_config_cc_proto
  modules::planning::reference_line::reference_line
)
add_library(modules::planning::tasks::deciders::st_bounds_decider::st_driving_limits  ALIAS   modules_planning_tasks_deciders_st_bounds_decider_st_driving_limits)

add_library(modules_planning_tasks_deciders_st_bounds_decider_st_obstacles_processor  SHARED
  st_obstacles_processor.cc
)
set_target_properties(modules_planning_tasks_deciders_st_bounds_decider_st_obstacles_processor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_st_bounds_decider_st_obstacles_processor
  modules::common::configs::vehicle_config_helper
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::map::pnc_map::pnc_map
  modules::planning::common::frame
  modules::planning::common::history
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
add_library(modules::planning::tasks::deciders::st_bounds_decider::st_obstacles_processor  ALIAS   modules_planning_tasks_deciders_st_bounds_decider_st_obstacles_processor)

