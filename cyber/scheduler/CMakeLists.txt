cmake_minimum_required(VERSION 3.16)

project(cyber_scheduler)
message("${Green} [info] cyber_scheduler cmakelist ${ColourReset}")

add_library(cyber_scheduler_processor  SHARED
  processor.cc
)
set_target_properties(cyber_scheduler_processor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_scheduler_processor
  cyber::data::data
  cyber::scheduler::processor_context
)
add_library(cyber::scheduler::processor  ALIAS   cyber_scheduler_processor)

add_library(cyber_scheduler_processor_context  SHARED
  processor_context.cc
)
set_target_properties(cyber_scheduler_processor_context  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_scheduler_processor_context
  cyber::croutine::croutine
  cyber::data::data
)
add_library(cyber::scheduler::processor_context  ALIAS   cyber_scheduler_processor_context)

add_library(cyber_scheduler_scheduler  SHARED
  scheduler.cc
)
set_target_properties(cyber_scheduler_scheduler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_scheduler_scheduler
  cyber::croutine::croutine
  cyber::scheduler::mutex_wrapper
  cyber::scheduler::pin_thread
  cyber::scheduler::processor
)
add_library(cyber::scheduler::scheduler  ALIAS   cyber_scheduler_scheduler)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_scheduler_mutex_wrapper  SHARED
  ${virtual_cc}
  common/mutex_wrapper.h
)
set_target_properties(cyber_scheduler_mutex_wrapper  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::scheduler::mutex_wrapper  ALIAS   cyber_scheduler_mutex_wrapper)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_scheduler_cv_wrapper  SHARED
  ${virtual_cc}
  common/cv_wrapper.h
)
set_target_properties(cyber_scheduler_cv_wrapper  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::scheduler::cv_wrapper  ALIAS   cyber_scheduler_cv_wrapper)

add_library(cyber_scheduler_pin_thread  SHARED
  common/pin_thread.cc
)
set_target_properties(cyber_scheduler_pin_thread  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_scheduler_pin_thread
  cyber::common::log
)
add_library(cyber::scheduler::pin_thread  ALIAS   cyber_scheduler_pin_thread)

add_library(cyber_scheduler_scheduler_factory  SHARED
  scheduler_factory.cc
)
set_target_properties(cyber_scheduler_scheduler_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_scheduler_scheduler_factory
  cyber::proto::component_conf_cc_proto
  cyber::scheduler::scheduler_choreography
  cyber::scheduler::scheduler_classic
)
add_library(cyber::scheduler::scheduler_factory  ALIAS   cyber_scheduler_scheduler_factory)

add_library(cyber_scheduler_scheduler_choreography  SHARED
  policy/scheduler_choreography.cc
)
set_target_properties(cyber_scheduler_scheduler_choreography  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_scheduler_scheduler_choreography
  cyber::scheduler::scheduler
  cyber::scheduler::choreography_context
  cyber::scheduler::classic_context
)
add_library(cyber::scheduler::scheduler_choreography  ALIAS   cyber_scheduler_scheduler_choreography)

add_library(cyber_scheduler_scheduler_classic  SHARED
  policy/scheduler_classic.cc
)
set_target_properties(cyber_scheduler_scheduler_classic  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_scheduler_scheduler_classic
  cyber::scheduler::scheduler
  cyber::scheduler::classic_context
)
add_library(cyber::scheduler::scheduler_classic  ALIAS   cyber_scheduler_scheduler_classic)

add_library(cyber_scheduler_choreography_context  SHARED
  policy/choreography_context.cc
)
set_target_properties(cyber_scheduler_choreography_context  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_scheduler_choreography_context
  cyber::croutine::croutine
  cyber::proto::choreography_conf_cc_proto
  cyber::scheduler::processor
)
add_library(cyber::scheduler::choreography_context  ALIAS   cyber_scheduler_choreography_context)

add_library(cyber_scheduler_classic_context  SHARED
  policy/classic_context.cc
)
set_target_properties(cyber_scheduler_classic_context  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_scheduler_classic_context
  cyber::croutine::croutine
  cyber::proto::classic_conf_cc_proto
  cyber::scheduler::cv_wrapper
  cyber::scheduler::mutex_wrapper
  cyber::scheduler::processor
)
add_library(cyber::scheduler::classic_context  ALIAS   cyber_scheduler_classic_context)

