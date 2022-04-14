cmake_minimum_required(VERSION 3.16)

project(modules_planning_planner_navi)
message("${Green} [info] modules_planning_planner_navi cmakelist ${ColourReset}")

add_library(modules_planning_planner_navi_navi_planner  SHARED
  navi_planner.cc
)
set_target_properties(modules_planning_planner_navi_navi_planner  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_planner_navi_navi_planner
  cyber::common::log
  cyber::time::clock
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::common::util::util
  modules::common::util::factory
  modules::common::vehicle_state::vehicle_state_provider
  modules::map::hdmap::hdmap
  modules::planning::common::planning_common
  modules::planning::constraint_checker::constraint_checker
  modules::planning::math::curve1d::quartic_polynomial_curve1d
  modules::planning::navi::decider::navi_obstacle_decider
  modules::planning::navi::decider::navi_path_decider
  modules::planning::navi::decider::navi_speed_decider
  modules::planning::planner::planner
  modules::planning::proto::planning_cc_proto
  modules::planning::reference_line::reference_line
  modules::planning::reference_line::qp_spline_reference_line_smoother
  ${gflags_LIBRARIES}
)
add_library(modules::planning::planner::navi::navi_planner  ALIAS   modules_planning_planner_navi_navi_planner)

