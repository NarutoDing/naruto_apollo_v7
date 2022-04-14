cmake_minimum_required(VERSION 3.16)

project(modules_planning_planner_public_road)
message("${Green} [info] modules_planning_planner_public_road cmakelist ${ColourReset}")

add_library(modules_planning_planner_public_road_public_road_planner  SHARED
  public_road_planner.cc
)
set_target_properties(modules_planning_planner_public_road_public_road_planner  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_planner_public_road_public_road_planner
  cyber::common::log
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::common::util::util
  modules::common::util::factory
  modules::common::vehicle_state::vehicle_state_provider
  modules::map::hdmap::hdmap
  modules::planning::common::planning_common
  modules::planning::common::planning_gflags
  modules::planning::constraint_checker::constraint_checker
  modules::planning::math::curve1d::quartic_polynomial_curve1d
  modules::planning::planner::planner
  modules::planning::proto::planning_cc_proto
  modules::planning::reference_line::reference_line
  modules::planning::reference_line::qp_spline_reference_line_smoother
  modules::planning::tasks::task
  modules::planning::tasks::deciders::path_decider::path_decider
  modules::planning::tasks::deciders::speed_decider::speed_decider
  modules::planning::tasks::optimizers::path_optimizer
  modules::planning::tasks::optimizers::speed_optimizer
  modules::planning::tasks::optimizers::path_time_heuristic::path_time_heuristic_optimizer
  ${gflags_LIBRARIES}
  ${eigen}
)
add_library(modules::planning::planner::public_road::public_road_planner  ALIAS   modules_planning_planner_public_road_public_road_planner)

