cmake_minimum_required(VERSION 3.16)

project(cyber_task)
message("${Green} [info] cyber_task cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_task_task  SHARED
  ${virtual_cc}
  task.h
)
set_target_properties(cyber_task_task  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_task_task
  cyber::task::task_manager
)
add_library(cyber::task::task  ALIAS   cyber_task_task)

add_library(cyber_task_task_manager  SHARED
  task_manager.cc
)
set_target_properties(cyber_task_task_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_task_task_manager
  cyber::scheduler::scheduler_factory
)
add_library(cyber::task::task_manager  ALIAS   cyber_task_task_manager)

