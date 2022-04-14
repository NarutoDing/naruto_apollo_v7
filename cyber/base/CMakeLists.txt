cmake_minimum_required(VERSION 3.16)

project(cyber_base)
message("${Green} [info] cyber_base cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_base  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_base_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_base_base
  cyber::base::atomic_hash_map
  cyber::base::atomic_rw_lock
  cyber::base::bounded_queue
  cyber::base::concurrent_object_pool
  cyber::base::for_each
  cyber::base::macros
  cyber::base::object_pool
  cyber::base::reentrant_rw_lock
  cyber::base::rw_lock_guard
  cyber::base::signal
  cyber::base::thread_pool
  cyber::base::thread_safe_queue
  cyber::base::unbounded_queue
  cyber::base::wait_strategy
)
add_library(cyber::base::base  ALIAS   cyber_base_base)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_atomic_hash_map  SHARED
  ${virtual_cc}
  atomic_hash_map.h
)
set_target_properties(cyber_base_atomic_hash_map  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::base::atomic_hash_map  ALIAS   cyber_base_atomic_hash_map)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_atomic_rw_lock  SHARED
  ${virtual_cc}
  atomic_rw_lock.h
)
set_target_properties(cyber_base_atomic_rw_lock  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_base_atomic_rw_lock
  cyber::base::rw_lock_guard
)
add_library(cyber::base::atomic_rw_lock  ALIAS   cyber_base_atomic_rw_lock)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_bounded_queue  SHARED
  ${virtual_cc}
  bounded_queue.h
)
set_target_properties(cyber_base_bounded_queue  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_base_bounded_queue
  cyber::base::macros
  cyber::base::wait_strategy
)
add_library(cyber::base::bounded_queue  ALIAS   cyber_base_bounded_queue)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_concurrent_object_pool  SHARED
  ${virtual_cc}
  concurrent_object_pool.h
)
set_target_properties(cyber_base_concurrent_object_pool  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_base_concurrent_object_pool
  cyber::base::for_each
)
add_library(cyber::base::concurrent_object_pool  ALIAS   cyber_base_concurrent_object_pool)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_for_each  SHARED
  ${virtual_cc}
  for_each.h
)
set_target_properties(cyber_base_for_each  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_base_for_each
  cyber::base::macros
)
add_library(cyber::base::for_each  ALIAS   cyber_base_for_each)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_macros  SHARED
  ${virtual_cc}
  macros.h
)
set_target_properties(cyber_base_macros  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::base::macros  ALIAS   cyber_base_macros)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_object_pool  SHARED
  ${virtual_cc}
  object_pool.h
)
set_target_properties(cyber_base_object_pool  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_base_object_pool
  cyber::base::for_each
  cyber::base::macros
)
add_library(cyber::base::object_pool  ALIAS   cyber_base_object_pool)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_reentrant_rw_lock  SHARED
  ${virtual_cc}
  reentrant_rw_lock.h
)
set_target_properties(cyber_base_reentrant_rw_lock  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::base::reentrant_rw_lock  ALIAS   cyber_base_reentrant_rw_lock)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_rw_lock_guard  SHARED
  ${virtual_cc}
  rw_lock_guard.h
)
set_target_properties(cyber_base_rw_lock_guard  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::base::rw_lock_guard  ALIAS   cyber_base_rw_lock_guard)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_signal  SHARED
  ${virtual_cc}
  signal.h
)
set_target_properties(cyber_base_signal  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::base::signal  ALIAS   cyber_base_signal)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_thread_pool  SHARED
  ${virtual_cc}
  thread_pool.h
)
set_target_properties(cyber_base_thread_pool  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::base::thread_pool  ALIAS   cyber_base_thread_pool)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_thread_safe_queue  SHARED
  ${virtual_cc}
  thread_safe_queue.h
)
set_target_properties(cyber_base_thread_safe_queue  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::base::thread_safe_queue  ALIAS   cyber_base_thread_safe_queue)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_unbounded_queue  SHARED
  ${virtual_cc}
  unbounded_queue.h
)
set_target_properties(cyber_base_unbounded_queue  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::base::unbounded_queue  ALIAS   cyber_base_unbounded_queue)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_base_wait_strategy  SHARED
  ${virtual_cc}
  wait_strategy.h
)
set_target_properties(cyber_base_wait_strategy  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::base::wait_strategy  ALIAS   cyber_base_wait_strategy)

