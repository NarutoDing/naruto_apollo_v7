cmake_minimum_required(VERSION 3.16)

project(modules_planning_open_space_tools)
message("${Green} [info] modules_planning_open_space_tools cmakelist ${ColourReset}")

add_library(hybrid_a_star_wrapper_lib  SHARED
  hybrid_a_star_wrapper.cc
)
set_target_properties(hybrid_a_star_wrapper_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(hybrid_a_star_wrapper_lib
  modules::planning::open_space::coarse_trajectory_generator::hybrid_a_star
)
add_library(distance_approach_problem_wrapper_lib  SHARED
  distance_approach_problem_wrapper.cc
)
set_target_properties(distance_approach_problem_wrapper_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(distance_approach_problem_wrapper_lib
  modules::planning::open_space::coarse_trajectory_generator::hybrid_a_star
  modules::planning::open_space::trajectory_smoother::distance_approach_problem
  modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_problem
)
add_library(open_space_roi_wrapper_lib  SHARED
  open_space_roi_wrapper.cc
)
set_target_properties(open_space_roi_wrapper_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(open_space_roi_wrapper_lib
  cyber::common::log
  modules::common::math::math
  modules::map::pnc_map::pnc_map
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  ${eigen}
)
