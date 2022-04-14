cmake_minimum_required(VERSION 3.16)

project(modules_planning_math_piecewise_jerk)
message("${Green} [info] modules_planning_math_piecewise_jerk cmakelist ${ColourReset}")

add_library(modules_planning_math_piecewise_jerk_piecewise_jerk_problem  SHARED
  piecewise_jerk_problem.cc
)
set_target_properties(modules_planning_math_piecewise_jerk_piecewise_jerk_problem  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_piecewise_jerk_piecewise_jerk_problem
  cyber::common::log
  modules::planning::common::planning_gflags
  ${osqp}
)
add_library(modules::planning::math::piecewise_jerk::piecewise_jerk_problem  ALIAS   modules_planning_math_piecewise_jerk_piecewise_jerk_problem)

add_library(modules_planning_math_piecewise_jerk_piecewise_jerk_path_problem  SHARED
  piecewise_jerk_path_problem.cc
)
set_target_properties(modules_planning_math_piecewise_jerk_piecewise_jerk_path_problem  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_piecewise_jerk_piecewise_jerk_path_problem
  modules::planning::math::piecewise_jerk::piecewise_jerk_problem
)
add_library(modules::planning::math::piecewise_jerk::piecewise_jerk_path_problem  ALIAS   modules_planning_math_piecewise_jerk_piecewise_jerk_path_problem)

add_library(modules_planning_math_piecewise_jerk_piecewise_jerk_speed_problem  SHARED
  piecewise_jerk_speed_problem.cc
)
set_target_properties(modules_planning_math_piecewise_jerk_piecewise_jerk_speed_problem  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_piecewise_jerk_piecewise_jerk_speed_problem
  modules::planning::math::piecewise_jerk::piecewise_jerk_problem
)
add_library(modules::planning::math::piecewise_jerk::piecewise_jerk_speed_problem  ALIAS   modules_planning_math_piecewise_jerk_piecewise_jerk_speed_problem)

