cmake_minimum_required(VERSION 3.16)

project(modules_planning_reference_line)
message("${Green} [info] modules_planning_reference_line cmakelist ${ColourReset}")

add_library(modules_planning_reference_line_reference_line  SHARED
  reference_line.cc
  reference_point.cc
)
set_target_properties(modules_planning_reference_line_reference_line  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_reference_line_reference_line
  cyber::common::log
  modules::common::math::math
  modules::common::proto::pnc_point_cc_proto
  modules::common::util::map_util
  modules::common::util::point_factory
  modules::map::pnc_map::path
  modules::planning::common::planning_gflags
  modules::planning::proto::planning_cc_proto
  ${absl}
)
add_library(modules::planning::reference_line::reference_line  ALIAS   modules_planning_reference_line_reference_line)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_reference_line_reference_line_smoother  SHARED
  ${virtual_cc}
  reference_line_smoother.h
)
set_target_properties(modules_planning_reference_line_reference_line_smoother  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_reference_line_reference_line_smoother
  modules::planning::proto::reference_line_smoother_config_cc_proto
)
add_library(modules::planning::reference_line::reference_line_smoother  ALIAS   modules_planning_reference_line_reference_line_smoother)

add_library(modules_planning_reference_line_qp_spline_reference_line_smoother  SHARED
  qp_spline_reference_line_smoother.cc
)
set_target_properties(modules_planning_reference_line_qp_spline_reference_line_smoother  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_reference_line_qp_spline_reference_line_smoother
  modules::planning::reference_line::reference_line
  modules::planning::reference_line::reference_line_smoother
  modules::planning::math::curve_math
  modules::planning::math::polynomial_xd
  modules::planning::math::smoothing_spline::osqp_spline_2d_solver
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::reference_line_smoother_config_cc_proto
  ${eigen}
)
add_library(modules::planning::reference_line::qp_spline_reference_line_smoother  ALIAS   modules_planning_reference_line_qp_spline_reference_line_smoother)

add_library(modules_planning_reference_line_spiral_reference_line_smoother  SHARED
  spiral_problem_interface.cc
  spiral_reference_line_smoother.cc
)
set_target_properties(modules_planning_reference_line_spiral_reference_line_smoother  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_reference_line_spiral_reference_line_smoother
  modules::planning::reference_line::reference_line
  modules::planning::reference_line::reference_line_smoother
  modules::common::math::math
  modules::planning::common::planning_gflags
  modules::planning::math::curve1d::quintic_spiral_path
  modules::planning::math::smoothing_spline::spline_2d_solver
  modules::planning::proto::planning_cc_proto
  ${eigen}
  ${ipopt}
)
add_library(modules::planning::reference_line::spiral_reference_line_smoother  ALIAS   modules_planning_reference_line_spiral_reference_line_smoother)

add_library(modules_planning_reference_line_discrete_points_reference_line_smoother  SHARED
  discrete_points_reference_line_smoother.cc
)
set_target_properties(modules_planning_reference_line_discrete_points_reference_line_smoother  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_reference_line_discrete_points_reference_line_smoother
  modules::planning::reference_line::reference_line
  modules::planning::reference_line::reference_line_smoother
  modules::common::math::math
  modules::planning::common::planning_gflags
  modules::planning::math::discrete_points_math
  modules::planning::math::discretized_points_smoothing::cos_theta_smoother
  modules::planning::math::discretized_points_smoothing::fem_pos_deviation_smoother
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::reference_line_smoother_config_cc_proto
)
add_library(modules::planning::reference_line::discrete_points_reference_line_smoother  ALIAS   modules_planning_reference_line_discrete_points_reference_line_smoother)

add_library(modules_planning_reference_line_reference_line_provider  SHARED
  reference_line_provider.cc
)
set_target_properties(modules_planning_reference_line_reference_line_provider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_reference_line_reference_line_provider
  modules::planning::reference_line::discrete_points_reference_line_smoother
  modules::planning::reference_line::qp_spline_reference_line_smoother
  modules::planning::reference_line::reference_line
  modules::planning::reference_line::spiral_reference_line_smoother
  cyber::time::clock
  modules::common::configs::vehicle_config_helper
  modules::common::util::factory
  modules::common::vehicle_state::vehicle_state_provider
  modules::map::pnc_map::pnc_map
  modules::planning::common::indexed_queue
  modules::planning::common::planning_context
  modules::planning::proto::planning_config_cc_proto
  modules::planning::proto::planning_status_cc_proto
  ${eigen}
)
add_library(modules::planning::reference_line::reference_line_provider  ALIAS   modules_planning_reference_line_reference_line_provider)

add_executable(smoother_util
  smoother_util.cc
)
target_link_libraries(smoother_util
  modules::planning::reference_line::discrete_points_reference_line_smoother
  modules::planning::reference_line::qp_spline_reference_line_smoother
  modules::planning::reference_line::reference_line
  modules::planning::reference_line::spiral_reference_line_smoother
  modules::planning::proto::planning_config_cc_proto
)
add_executable(spiral_smoother_util
  spiral_smoother_util.cc
)
target_link_libraries(spiral_smoother_util
  modules::planning::reference_line::spiral_reference_line_smoother
  modules::planning::proto::planning_config_cc_proto
)
