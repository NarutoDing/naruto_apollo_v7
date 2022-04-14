cmake_minimum_required(VERSION 3.16)

project(cyber_time)
message("${Green} [info] cyber_time cmakelist ${ColourReset}")

add_library(cyber_time_time  SHARED
  time.cc
)
set_target_properties(cyber_time_time  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_time_time
  cyber::time::duration
)
add_library(cyber::time::time  ALIAS   cyber_time_time)

add_library(cyber_time_rate  SHARED
  rate.cc
)
set_target_properties(cyber_time_rate  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_time_rate
  cyber::time::duration
  cyber::time::time
  cyber::common::log
)
add_library(cyber::time::rate  ALIAS   cyber_time_rate)

add_library(cyber_time_duration  SHARED
  duration.cc
)
set_target_properties(cyber_time_duration  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::time::duration  ALIAS   cyber_time_duration)

add_library(cyber_time_clock  SHARED
  clock.cc
)
set_target_properties(cyber_time_clock  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_time_clock
  cyber::time::time
  cyber::base::atomic_rw_lock
  cyber::common::global_data
  cyber::common::log
  cyber::common::macros
  cyber::common::util
  cyber::proto::run_mode_conf_cc_proto
)
add_library(cyber::time::clock  ALIAS   cyber_time_clock)

