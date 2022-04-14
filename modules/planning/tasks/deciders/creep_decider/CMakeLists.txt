cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_creep_decider)
message("${Green} [info] modules_planning_tasks_deciders_creep_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_creep_decider_creep_decider  SHARED
  creep_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_creep_decider_creep_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_creep_decider_creep_decider
  modules::planning::common::planning_context
  modules::planning::common::reference_line_info
  modules::planning::common::util::common_lib
  modules::planning::common::util::util_lib
  modules::planning::scenarios::util::scenario_util_lib
  modules::planning::tasks::deciders::decider_base
)
add_library(modules::planning::tasks::deciders::creep_decider::creep_decider  ALIAS   modules_planning_tasks_deciders_creep_decider_creep_decider)

