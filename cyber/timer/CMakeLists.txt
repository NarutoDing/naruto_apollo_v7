cmake_minimum_required(VERSION 3.16)

project(cyber_timer)
message("${Green} [info] cyber_timer cmakelist ${ColourReset}")

add_library(cyber_timer_timer  SHARED
  timer.cc
)
set_target_properties(cyber_timer_timer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_timer_timer
  cyber::timer::timing_wheel
  cyber::common::global_data
)
add_library(cyber::timer::timer  ALIAS   cyber_timer_timer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_timer_timer_task  SHARED
  ${virtual_cc}
  timer_task.h
)
set_target_properties(cyber_timer_timer_task  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::timer::timer_task  ALIAS   cyber_timer_timer_task)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_timer_timer_bucket  SHARED
  ${virtual_cc}
  timer_bucket.h
)
set_target_properties(cyber_timer_timer_bucket  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_timer_timer_bucket
  cyber::timer::timer_task
)
add_library(cyber::timer::timer_bucket  ALIAS   cyber_timer_timer_bucket)

add_library(cyber_timer_timing_wheel  SHARED
  timing_wheel.cc
)
set_target_properties(cyber_timer_timing_wheel  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_timer_timing_wheel
  cyber::timer::timer_bucket
  cyber::task::task
  cyber::time::time
  cyber::time::duration
  cyber::time::rate
)
add_library(cyber::timer::timing_wheel  ALIAS   cyber_timer_timing_wheel)

