cmake_minimum_required(VERSION 3.16)

project(cyber_component)
message("${Green} [info] cyber_component cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_component_component  SHARED
  ${virtual_cc}
  component.h
)
set_target_properties(cyber_component_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_component_component
  cyber::component::component_base
  cyber::scheduler::scheduler
)
add_library(cyber::component::component  ALIAS   cyber_component_component)

add_library(cyber_component_timer_component  SHARED
  timer_component.cc
)
set_target_properties(cyber_component_timer_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_component_timer_component
  cyber::component::component_base
  cyber::blocker::blocker_manager
  cyber::timer::timer
  cyber::transport::message::history
  cyber::transport::transmitter::transmitter
)
add_library(cyber::component::timer_component  ALIAS   cyber_component_timer_component)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_component_component_base  SHARED
  ${virtual_cc}
  component_base.h
)
set_target_properties(cyber_component_component_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_component_component_base
  cyber::base::signal
  cyber::base::thread_pool
  cyber::class_loader::class_loader
  cyber::node::node
  ${gflags_LIBRARIES}
)
add_library(cyber::component::component_base  ALIAS   cyber_component_component_base)

