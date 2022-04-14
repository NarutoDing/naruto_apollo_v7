cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_path_lane_borrow_decider)
message("${Green} [info] modules_planning_tasks_deciders_path_lane_borrow_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_path_lane_borrow_decider_path_lane_borrow_decider  SHARED
  path_lane_borrow_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_path_lane_borrow_decider_path_lane_borrow_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_path_lane_borrow_decider_path_lane_borrow_decider
  modules::planning::common::obstacle_blocking_analyzer
  modules::planning::common::planning_context
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::tasks::deciders::decider_base
)
add_library(modules::planning::tasks::deciders::path_lane_borrow_decider::path_lane_borrow_decider  ALIAS   modules_planning_tasks_deciders_path_lane_borrow_decider_path_lane_borrow_decider)

