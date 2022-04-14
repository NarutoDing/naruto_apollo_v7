cmake_minimum_required(VERSION 3.16)

project(modules_planning_navi_decider)
message("${Green} [info] modules_planning_navi_decider cmakelist ${ColourReset}")

add_library(modules_planning_navi_decider_navi_task  SHARED
  navi_task.cc
)
set_target_properties(modules_planning_navi_decider_navi_task  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_navi_decider_navi_task
  cyber::common::log
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::common::trajectory::publishable_trajectory
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
)
add_library(modules::planning::navi::decider::navi_task  ALIAS   modules_planning_navi_decider_navi_task)

add_library(modules_planning_navi_decider_navi_path_decider  SHARED
  navi_path_decider.cc
)
set_target_properties(modules_planning_navi_decider_navi_path_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_navi_decider_navi_path_decider
  modules::planning::navi::decider::navi_task
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::navi::decider::navi_obstacle_decider
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::tasks::task
)
add_library(modules::planning::navi::decider::navi_path_decider  ALIAS   modules_planning_navi_decider_navi_path_decider)

add_library(modules_planning_navi_decider_navi_speed_decider  SHARED
  navi_speed_decider.cc
  navi_speed_ts_graph.cc
)
set_target_properties(modules_planning_navi_decider_navi_speed_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_navi_decider_navi_speed_decider
  modules::planning::navi::decider::navi_task
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::navi::decider::navi_obstacle_decider
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::tasks::task
)
add_library(modules::planning::navi::decider::navi_speed_decider  ALIAS   modules_planning_navi_decider_navi_speed_decider)

add_library(modules_planning_navi_decider_navi_obstacle_decider  SHARED
  navi_obstacle_decider.cc
)
set_target_properties(modules_planning_navi_decider_navi_obstacle_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_navi_decider_navi_obstacle_decider
  modules::planning::navi::decider::navi_task
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::math::path_matcher
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::tasks::task
)
add_library(modules::planning::navi::decider::navi_obstacle_decider  ALIAS   modules_planning_navi_decider_navi_obstacle_decider)

