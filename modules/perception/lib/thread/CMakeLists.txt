cmake_minimum_required(VERSION 3.16)

project(modules_perception_lib_thread)
message("${Green} [info] modules_perception_lib_thread cmakelist ${ColourReset}")

add_library(modules_perception_lib_thread_thread  SHARED
  thread.cc
  thread_pool.cc
  thread_worker.cc
)
set_target_properties(modules_perception_lib_thread_thread  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lib_thread_thread
  cyber::cyber
)
add_library(modules::perception::lib::thread::thread  ALIAS   modules_perception_lib_thread_thread)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lib_thread_concurrent_queue  SHARED
  ${virtual_cc}
  concurrent_queue.h
)
set_target_properties(modules_perception_lib_thread_concurrent_queue  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lib::thread::concurrent_queue  ALIAS   modules_perception_lib_thread_concurrent_queue)

