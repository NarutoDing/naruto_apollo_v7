cmake_minimum_required(VERSION 3.16)

project(modules_task_manager_common)
message("${Green} [info] modules_task_manager_common cmakelist ${ColourReset}")

add_library(modules_task_manager_common_task_manager_gflags  SHARED
  task_manager_gflags.cc
)
set_target_properties(modules_task_manager_common_task_manager_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_task_manager_common_task_manager_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::task_manager::common::task_manager_gflags  ALIAS   modules_task_manager_common_task_manager_gflags)

