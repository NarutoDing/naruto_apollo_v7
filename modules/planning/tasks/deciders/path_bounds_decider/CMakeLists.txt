cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_path_bounds_decider)
message("${Green} [info] modules_planning_tasks_deciders_path_bounds_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_path_bounds_decider_path_bounds_decider  SHARED
  path_bounds_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_path_bounds_decider_path_bounds_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_path_bounds_decider_path_bounds_decider
  modules::planning::common::planning_context
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::tasks::deciders::decider_base
  modules::planning::tasks::deciders::utils::path_decider_obstacle_utils
)
add_library(modules::planning::tasks::deciders::path_bounds_decider::path_bounds_decider  ALIAS   modules_planning_tasks_deciders_path_bounds_decider_path_bounds_decider)

