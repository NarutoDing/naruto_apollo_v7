cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_open_space_decider)
message("${Green} [info] modules_planning_tasks_deciders_open_space_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_open_space_decider_open_space_roi_decider  SHARED
  open_space_roi_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_open_space_decider_open_space_roi_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_open_space_decider_open_space_roi_decider
  modules::dreamview::backend::map::map_service
  modules::planning::common::planning_context
  modules::planning::common::planning_gflags
  modules::planning::tasks::deciders::decider_base
)
add_library(modules::planning::tasks::deciders::open_space_decider::open_space_roi_decider  ALIAS   modules_planning_tasks_deciders_open_space_decider_open_space_roi_decider)

add_library(modules_planning_tasks_deciders_open_space_decider_open_space_pre_stop_decider  SHARED
  open_space_pre_stop_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_open_space_decider_open_space_pre_stop_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_open_space_decider_open_space_pre_stop_decider
  modules::planning::common::reference_line_info
  modules::planning::common::util::common_lib
  modules::planning::tasks::deciders::decider_base
)
add_library(modules::planning::tasks::deciders::open_space_decider::open_space_pre_stop_decider  ALIAS   modules_planning_tasks_deciders_open_space_decider_open_space_pre_stop_decider)

add_library(modules_planning_tasks_deciders_open_space_decider_open_space_fallback_decider  SHARED
  open_space_fallback_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_open_space_decider_open_space_fallback_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_open_space_decider_open_space_fallback_decider
  modules::planning::common::dependency_injector
  modules::planning::common::planning_context
  modules::planning::common::planning_gflags
  modules::planning::tasks::deciders::decider_base
)
add_library(modules::planning::tasks::deciders::open_space_decider::open_space_fallback_decider  ALIAS   modules_planning_tasks_deciders_open_space_decider_open_space_fallback_decider)

