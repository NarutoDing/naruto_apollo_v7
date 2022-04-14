cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_lane_follow)
message("${Green} [info] modules_planning_scenarios_lane_follow cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_scenarios_lane_follow_lane_follow  SHARED
  ${virtual_cc}
)
set_target_properties(modules_planning_scenarios_lane_follow_lane_follow  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_lane_follow_lane_follow
  modules::planning::scenarios::lane_follow::lane_follow_scenario
  modules::planning::scenarios::lane_follow::lane_follow_stage
)
add_library(modules::planning::scenarios::lane_follow::lane_follow  ALIAS   modules_planning_scenarios_lane_follow_lane_follow)

add_library(modules_planning_scenarios_lane_follow_lane_follow_stage  SHARED
  lane_follow_stage.cc
)
set_target_properties(modules_planning_scenarios_lane_follow_lane_follow_stage  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_lane_follow_lane_follow_stage
  cyber::common::log
  cyber::time::clock
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::common::util::util
  modules::common::util::factory
  modules::common::vehicle_state::vehicle_state_provider
  modules::map::hdmap::hdmap
  modules::planning::common::planning_common
  modules::planning::common::speed_profile_generator
  modules::planning::constraint_checker::constraint_checker
  modules::planning::math::curve1d::quartic_polynomial_curve1d
  modules::planning::proto::planning_cc_proto
  modules::planning::reference_line::reference_line
  modules::planning::reference_line::qp_spline_reference_line_smoother
  modules::planning::scenarios::scenario
  modules::planning::tasks::deciders::lane_change_decider::lane_change_decider
  modules::planning::tasks::deciders::path_decider::path_decider
  modules::planning::tasks::deciders::speed_decider::speed_decider
  modules::planning::tasks::optimizers::path_optimizer
  modules::planning::tasks::optimizers::speed_optimizer
  modules::planning::tasks::optimizers::path_time_heuristic::path_time_heuristic_optimizer
  ${gflags_LIBRARIES}
  ${eigen}
)
add_library(modules::planning::scenarios::lane_follow::lane_follow_stage  ALIAS   modules_planning_scenarios_lane_follow_lane_follow_stage)

add_library(modules_planning_scenarios_lane_follow_lane_follow_scenario  SHARED
  lane_follow_scenario.cc
)
set_target_properties(modules_planning_scenarios_lane_follow_lane_follow_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_lane_follow_lane_follow_scenario
  modules::planning::scenarios::lane_follow::lane_follow_stage
  cyber::common::log
  cyber::time::clock
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::common::util::util
  modules::common::util::factory
  modules::common::vehicle_state::vehicle_state_provider
  modules::map::hdmap::hdmap
  modules::planning::common::planning_common
  modules::planning::common::speed_profile_generator
  modules::planning::constraint_checker::constraint_checker
  modules::planning::math::curve1d::quartic_polynomial_curve1d
  modules::planning::proto::planning_cc_proto
  modules::planning::reference_line::reference_line
  modules::planning::reference_line::qp_spline_reference_line_smoother
  modules::planning::scenarios::scenario
  modules::planning::tasks::deciders::path_decider::path_decider
  modules::planning::tasks::deciders::speed_decider::speed_decider
  modules::planning::tasks::optimizers::path_optimizer
  modules::planning::tasks::optimizers::speed_optimizer
  modules::planning::tasks::optimizers::path_time_heuristic::path_time_heuristic_optimizer
  ${gflags_LIBRARIES}
  ${eigen}
)
add_library(modules::planning::scenarios::lane_follow::lane_follow_scenario  ALIAS   modules_planning_scenarios_lane_follow_lane_follow_scenario)

