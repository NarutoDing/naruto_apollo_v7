cmake_minimum_required(VERSION 3.16)

project(modules_planning_planner_rtk)
message("${Green} [info] modules_planning_planner_rtk cmakelist ${ColourReset}")

add_library(modules_planning_planner_rtk_rtk_planner  SHARED
  rtk_replay_planner.cc
)
set_target_properties(modules_planning_planner_rtk_rtk_planner  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_planner_rtk_rtk_planner
  cyber::common::log
  modules::common::proto::pnc_point_cc_proto
  modules::common::util::util
  modules::common::util::factory
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::common::planning_common
  modules::planning::math::curve1d::quartic_polynomial_curve1d
  modules::planning::planner::planner
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
  ${gflags_LIBRARIES}
  ${absl}
  ${eigen}
)
add_library(modules::planning::planner::rtk::rtk_planner  ALIAS   modules_planning_planner_rtk_rtk_planner)

