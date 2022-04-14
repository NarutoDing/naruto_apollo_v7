cmake_minimum_required(VERSION 3.16)

project(modules_common_math)
message("${Green} [info] modules_common_math cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_math_math  SHARED
  ${virtual_cc}
)
set_target_properties(modules_common_math_math  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_math
  modules::common::math::angle
  modules::common::math::cartesian_frenet_conversion
  modules::common::math::curve_fitting
  modules::common::math::euler_angles_zxy
  modules::common::math::factorial
  modules::common::math::geometry
  modules::common::math::integral
  modules::common::math::kalman_filter
  modules::common::math::linear_interpolation
  modules::common::math::lqr
  modules::common::math::mpc_osqp
  modules::common::math::quaternion
  modules::common::math::search
  modules::common::math::sin_table
)
add_library(modules::common::math::math  ALIAS   modules_common_math_math)

add_library(modules_common_math_math_utils  SHARED
  math_utils.cc
)
set_target_properties(modules_common_math_math_utils  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_math_utils
  modules::common::math::vec2d
  ${eigen}
)
add_library(modules::common::math::math_utils  ALIAS   modules_common_math_math_utils)

add_library(modules_common_math_vec2d  SHARED
  vec2d.cc
)
set_target_properties(modules_common_math_vec2d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_vec2d
  cyber::common::log
  ${absl}
)
add_library(modules::common::math::vec2d  ALIAS   modules_common_math_vec2d)

add_library(modules_common_math_geometry  SHARED
  aabox2d.cc
  box2d.cc
  line_segment2d.cc
  polygon2d.cc
)
set_target_properties(modules_common_math_geometry  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_geometry
  modules::common::math::math_utils
  cyber::common::log
  modules::common::util::string_util
  ${absl}
  ${osqp}
)
add_library(modules::common::math::geometry  ALIAS   modules_common_math_geometry)

add_library(modules_common_math_sin_table  SHARED
  sin_table.cc
)
set_target_properties(modules_common_math_sin_table  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::math::sin_table  ALIAS   modules_common_math_sin_table)

add_library(modules_common_math_angle  SHARED
  angle.cc
)
set_target_properties(modules_common_math_angle  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_angle
  modules::common::math::sin_table
)
add_library(modules::common::math::angle  ALIAS   modules_common_math_angle)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_math_euler_angles_zxy  SHARED
  ${virtual_cc}
  euler_angles_zxy.h
)
set_target_properties(modules_common_math_euler_angles_zxy  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_euler_angles_zxy
  modules::common::math::geometry
  ${eigen}
)
add_library(modules::common::math::euler_angles_zxy  ALIAS   modules_common_math_euler_angles_zxy)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_math_quaternion  SHARED
  ${virtual_cc}
  quaternion.h
)
set_target_properties(modules_common_math_quaternion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_quaternion
  modules::common::math::euler_angles_zxy
  modules::common::math::geometry
  modules::common::proto::geometry_cc_proto
  ${eigen}
)
add_library(modules::common::math::quaternion  ALIAS   modules_common_math_quaternion)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_math_curve_fitting  SHARED
  ${virtual_cc}
  curve_fitting.h
)
set_target_properties(modules_common_math_curve_fitting  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_curve_fitting
  modules::common::math::matrix_operations
  ${eigen}
)
add_library(modules::common::math::curve_fitting  ALIAS   modules_common_math_curve_fitting)

add_library(modules_common_math_matrix_operations  SHARED
  matrix_operations.cc
)
set_target_properties(modules_common_math_matrix_operations  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_matrix_operations
  cyber::common::log
  ${eigen}
)
add_library(modules::common::math::matrix_operations  ALIAS   modules_common_math_matrix_operations)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_math_kalman_filter  SHARED
  ${virtual_cc}
  kalman_filter.h
)
set_target_properties(modules_common_math_kalman_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_kalman_filter
  cyber::common::log
  modules::common::math::matrix_operations
  ${eigen}
)
add_library(modules::common::math::kalman_filter  ALIAS   modules_common_math_kalman_filter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_math_factorial  SHARED
  ${virtual_cc}
  factorial.h
)
set_target_properties(modules_common_math_factorial  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::math::factorial  ALIAS   modules_common_math_factorial)

add_library(modules_common_math_path_matcher  SHARED
  path_matcher.cc
)
set_target_properties(modules_common_math_path_matcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_path_matcher
  modules::common::math::linear_interpolation
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::common::math::path_matcher  ALIAS   modules_common_math_path_matcher)

add_library(modules_common_math_mpc_osqp  SHARED
  mpc_osqp.cc
)
set_target_properties(modules_common_math_mpc_osqp  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_mpc_osqp
  cyber::common::log
  ${eigen}
  ${osqp}
)
add_library(modules::common::math::mpc_osqp  ALIAS   modules_common_math_mpc_osqp)

add_library(modules_common_math_search  SHARED
  search.cc
)
set_target_properties(modules_common_math_search  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::math::search  ALIAS   modules_common_math_search)

add_library(modules_common_math_linear_interpolation  SHARED
  linear_interpolation.cc
)
set_target_properties(modules_common_math_linear_interpolation  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_linear_interpolation
  modules::common::math::geometry
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::common::math::linear_interpolation  ALIAS   modules_common_math_linear_interpolation)

add_library(modules_common_math_integral  SHARED
  integral.cc
)
set_target_properties(modules_common_math_integral  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_integral
  cyber::common::log
)
add_library(modules::common::math::integral  ALIAS   modules_common_math_integral)

add_library(modules_common_math_lqr  SHARED
  linear_quadratic_regulator.cc
)
set_target_properties(modules_common_math_lqr  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_lqr
  cyber::common::log
  ${eigen}
)
add_library(modules::common::math::lqr  ALIAS   modules_common_math_lqr)

add_library(modules_common_math_cartesian_frenet_conversion  SHARED
  cartesian_frenet_conversion.cc
)
set_target_properties(modules_common_math_cartesian_frenet_conversion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_cartesian_frenet_conversion
  modules::common::math::geometry
  cyber::common::log
  ${eigen}
)
add_library(modules::common::math::cartesian_frenet_conversion  ALIAS   modules_common_math_cartesian_frenet_conversion)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_math_hermite_spline  SHARED
  ${virtual_cc}
  hermite_spline.h
)
set_target_properties(modules_common_math_hermite_spline  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_hermite_spline
  cyber::common::log
)
add_library(modules::common::math::hermite_spline  ALIAS   modules_common_math_hermite_spline)

