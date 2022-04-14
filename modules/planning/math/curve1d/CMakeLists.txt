cmake_minimum_required(VERSION 3.16)

project(modules_planning_math_curve1d)
message("${Green} [info] modules_planning_math_curve1d cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_math_curve1d_curve1d  SHARED
  ${virtual_cc}
  curve1d.h
)
set_target_properties(modules_planning_math_curve1d_curve1d  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::math::curve1d::curve1d  ALIAS   modules_planning_math_curve1d_curve1d)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_math_curve1d_polynomial_curve1d  SHARED
  ${virtual_cc}
  polynomial_curve1d.h
)
set_target_properties(modules_planning_math_curve1d_polynomial_curve1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_curve1d_polynomial_curve1d
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::math::curve1d::polynomial_curve1d  ALIAS   modules_planning_math_curve1d_polynomial_curve1d)

add_library(modules_planning_math_curve1d_quartic_polynomial_curve1d  SHARED
  quartic_polynomial_curve1d.cc
)
set_target_properties(modules_planning_math_curve1d_quartic_polynomial_curve1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_curve1d_quartic_polynomial_curve1d
  modules::planning::math::curve1d::polynomial_curve1d
  cyber::common::common
  modules::common::util::string_util
  ${absl}
)
add_library(modules::planning::math::curve1d::quartic_polynomial_curve1d  ALIAS   modules_planning_math_curve1d_quartic_polynomial_curve1d)

add_library(modules_planning_math_curve1d_quintic_polynomial_curve1d  SHARED
  quintic_polynomial_curve1d.cc
)
set_target_properties(modules_planning_math_curve1d_quintic_polynomial_curve1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_curve1d_quintic_polynomial_curve1d
  modules::planning::math::curve1d::polynomial_curve1d
  cyber::common::common
  modules::common::util::string_util
  ${absl}
)
add_library(modules::planning::math::curve1d::quintic_polynomial_curve1d  ALIAS   modules_planning_math_curve1d_quintic_polynomial_curve1d)

add_library(modules_planning_math_curve1d_cubic_polynomial_curve1d  SHARED
  cubic_polynomial_curve1d.cc
)
set_target_properties(modules_planning_math_curve1d_cubic_polynomial_curve1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_curve1d_cubic_polynomial_curve1d
  modules::planning::math::curve1d::polynomial_curve1d
  modules::planning::math::curve1d::quartic_polynomial_curve1d
  cyber::common::log
  ${absl}
)
add_library(modules::planning::math::curve1d::cubic_polynomial_curve1d  ALIAS   modules_planning_math_curve1d_cubic_polynomial_curve1d)

add_library(modules_planning_math_curve1d_quintic_spiral_path  SHARED
  quintic_spiral_path.cc
)
set_target_properties(modules_planning_math_curve1d_quintic_spiral_path  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_curve1d_quintic_spiral_path
  modules::planning::math::curve1d::quintic_polynomial_curve1d
  cyber::common::log
  modules::common::math::math
  ${absl}
)
add_library(modules::planning::math::curve1d::quintic_spiral_path  ALIAS   modules_planning_math_curve1d_quintic_spiral_path)

add_library(modules_planning_math_curve1d_piecewise_quintic_spiral_path  SHARED
  piecewise_quintic_spiral_path.cc
)
set_target_properties(modules_planning_math_curve1d_piecewise_quintic_spiral_path  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_curve1d_piecewise_quintic_spiral_path
  modules::planning::math::curve1d::quintic_spiral_path
  cyber::common::log
  modules::common::math::math
  ${absl}
)
add_library(modules::planning::math::curve1d::piecewise_quintic_spiral_path  ALIAS   modules_planning_math_curve1d_piecewise_quintic_spiral_path)

