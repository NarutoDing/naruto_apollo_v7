cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_utils)
message("${Green} [info] modules_planning_tasks_deciders_utils cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_utils_path_decider_obstacle_utils  SHARED
  path_decider_obstacle_utils.cc
)
set_target_properties(modules_planning_tasks_deciders_utils_path_decider_obstacle_utils  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_utils_path_decider_obstacle_utils
  modules::planning::common::frame
)
add_library(modules::planning::tasks::deciders::utils::path_decider_obstacle_utils  ALIAS   modules_planning_tasks_deciders_utils_path_decider_obstacle_utils)

