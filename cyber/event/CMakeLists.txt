cmake_minimum_required(VERSION 3.16)

project(cyber_event)
message("${Green} [info] cyber_event cmakelist ${ColourReset}")

add_library(cyber_event_perf_event_cache  SHARED
  perf_event_cache.cc
)
set_target_properties(cyber_event_perf_event_cache  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_event_perf_event_cache
  cyber::event::perf_event
  cyber::state
  cyber::base::bounded_queue
  cyber::common::global_data
  cyber::common::log
  cyber::common::macros
  cyber::time::time
)
add_library(cyber::event::perf_event_cache  ALIAS   cyber_event_perf_event_cache)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_event_perf_event  SHARED
  ${virtual_cc}
  perf_event.h
)
set_target_properties(cyber_event_perf_event  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_event_perf_event
  cyber::common::global_data
)
add_library(cyber::event::perf_event  ALIAS   cyber_event_perf_event)

