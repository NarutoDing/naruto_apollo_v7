cmake_minimum_required(VERSION 3.16)

project(cyber_croutine)
message("${Green} [info] cyber_croutine cmakelist ${ColourReset}")

add_library(cyber_croutine_croutine  SHARED
  croutine.cc
)
set_target_properties(cyber_croutine_croutine  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_croutine_croutine
  cyber::base::atomic_hash_map
  cyber::base::atomic_rw_lock
  cyber::base::bounded_queue
  cyber::base::concurrent_object_pool
  cyber::base::macros
  cyber::base::wait_strategy
  cyber::common::common
  cyber::croutine::routine_context
  cyber::croutine::routine_factory
  cyber::croutine::swap
  cyber::event::perf_event_cache
  cyber::time::time
  -latomic
)
add_library(cyber::croutine::croutine  ALIAS   cyber_croutine_croutine)

add_library(cyber_croutine_routine_context  SHARED
  detail/routine_context.cc
)
set_target_properties(cyber_croutine_routine_context  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_croutine_routine_context
  cyber::common::common
)
add_library(cyber::croutine::routine_context  ALIAS   cyber_croutine_routine_context)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_croutine_routine_factory  SHARED
  ${virtual_cc}
  routine_factory.h
)
set_target_properties(cyber_croutine_routine_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_croutine_routine_factory
  cyber::common::common
  cyber::event::perf_event_cache
)
add_library(cyber::croutine::routine_factory  ALIAS   cyber_croutine_routine_factory)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_croutine_swap  SHARED
  detail/swap_x86_64.S
  ${virtual_cc}
)
set_target_properties(cyber_croutine_swap  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::croutine::swap  ALIAS   cyber_croutine_swap)

