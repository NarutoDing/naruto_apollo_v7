cmake_minimum_required(VERSION 3.16)

project(modules_planning_common_trajectory1d)
message("${Green} [info] modules_planning_common_trajectory1d cmakelist ${ColourReset}")

add_library(modules_planning_common_trajectory1d_standing_still_trajectory1d  SHARED
  standing_still_trajectory1d.cc
)
set_target_properties(modules_planning_common_trajectory1d_standing_still_trajectory1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory1d_standing_still_trajectory1d
  cyber::common::log
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::common::trajectory1d::standing_still_trajectory1d  ALIAS   modules_planning_common_trajectory1d_standing_still_trajectory1d)

add_library(modules_planning_common_trajectory1d_piecewise_acceleration_trajectory1d  SHARED
  piecewise_acceleration_trajectory1d.cc
)
set_target_properties(modules_planning_common_trajectory1d_piecewise_acceleration_trajectory1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory1d_piecewise_acceleration_trajectory1d
  modules::common::math::linear_interpolation
  modules::planning::common::planning_gflags
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::common::trajectory1d::piecewise_acceleration_trajectory1d  ALIAS   modules_planning_common_trajectory1d_piecewise_acceleration_trajectory1d)

add_library(modules_planning_common_trajectory1d_constant_deceleration_trajectory1d  SHARED
  constant_deceleration_trajectory1d.cc
)
set_target_properties(modules_planning_common_trajectory1d_constant_deceleration_trajectory1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory1d_constant_deceleration_trajectory1d
  cyber::common::log
  modules::planning::common::planning_gflags
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::common::trajectory1d::constant_deceleration_trajectory1d  ALIAS   modules_planning_common_trajectory1d_constant_deceleration_trajectory1d)

add_library(modules_planning_common_trajectory1d_piecewise_trajectory1d  SHARED
  piecewise_trajectory1d.cc
)
set_target_properties(modules_planning_common_trajectory1d_piecewise_trajectory1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory1d_piecewise_trajectory1d
  modules::common::math::linear_interpolation
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::common::trajectory1d::piecewise_trajectory1d  ALIAS   modules_planning_common_trajectory1d_piecewise_trajectory1d)

add_library(modules_planning_common_trajectory1d_constant_jerk_trajectory1d  SHARED
  constant_jerk_trajectory1d.cc
)
set_target_properties(modules_planning_common_trajectory1d_constant_jerk_trajectory1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory1d_constant_jerk_trajectory1d
  cyber::common::log
  modules::planning::common::planning_gflags
  modules::planning::math::curve1d::curve1d
)
add_library(modules::planning::common::trajectory1d::constant_jerk_trajectory1d  ALIAS   modules_planning_common_trajectory1d_constant_jerk_trajectory1d)

add_library(modules_planning_common_trajectory1d_piecewise_jerk_trajectory1d  SHARED
  piecewise_jerk_trajectory1d.cc
)
set_target_properties(modules_planning_common_trajectory1d_piecewise_jerk_trajectory1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory1d_piecewise_jerk_trajectory1d
  modules::planning::common::trajectory1d::constant_jerk_trajectory1d
)
add_library(modules::planning::common::trajectory1d::piecewise_jerk_trajectory1d  ALIAS   modules_planning_common_trajectory1d_piecewise_jerk_trajectory1d)

