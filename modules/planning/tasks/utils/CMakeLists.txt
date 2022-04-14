cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_utils)
message("${Green} [info] modules_planning_tasks_utils cmakelist ${ColourReset}")

add_library(modules_planning_tasks_utils_st_gap_estimator  SHARED
  st_gap_estimator.cc
)
set_target_properties(modules_planning_tasks_utils_st_gap_estimator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_utils_st_gap_estimator
  modules::planning::common::planning_gflags
)
add_library(modules::planning::tasks::utils::st_gap_estimator  ALIAS   modules_planning_tasks_utils_st_gap_estimator)

