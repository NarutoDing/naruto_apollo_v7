cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders)
message("${Green} [info] modules_planning_tasks_deciders cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_decider_base  SHARED
  decider.cc
)
set_target_properties(modules_planning_tasks_deciders_decider_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_decider_base
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::tasks::task
)
add_library(modules::planning::tasks::deciders::decider_base  ALIAS   modules_planning_tasks_deciders_decider_base)

