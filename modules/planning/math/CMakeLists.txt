cmake_minimum_required(VERSION 3.16)

project(modules_planning_math)
message("${Green} [info] modules_planning_math cmakelist ${ColourReset}")

add_library(modules_planning_math_curve_math  SHARED
  curve_math.cc
)
set_target_properties(modules_planning_math_curve_math  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::math::curve_math  ALIAS   modules_planning_math_curve_math)

add_library(modules_planning_math_discrete_points_math  SHARED
  discrete_points_math.cc
)
set_target_properties(modules_planning_math_discrete_points_math  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_discrete_points_math
  cyber::common::log
)
add_library(modules::planning::math::discrete_points_math  ALIAS   modules_planning_math_discrete_points_math)

add_library(modules_planning_math_polynomial_xd  SHARED
  polynomial_xd.cc
)
set_target_properties(modules_planning_math_polynomial_xd  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_polynomial_xd
  cyber::common::log
)
add_library(modules::planning::math::polynomial_xd  ALIAS   modules_planning_math_polynomial_xd)

