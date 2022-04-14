cmake_minimum_required(VERSION 3.16)

project(cyber)
message("${Green} [info] cyber cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_cyber  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_cyber  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_cyber
  cyber::cyber_core
)
add_library(cyber::cyber  ALIAS   cyber_cyber)

add_library(cyber_binary  SHARED
  binary.cc
)
set_target_properties(cyber_binary  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::binary  ALIAS   cyber_binary)

add_library(cyber_state  SHARED
  state.cc
)
set_target_properties(cyber_state  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_state
  cyber::common::common
)
add_library(cyber::state  ALIAS   cyber_state)

add_library(cyber_init  SHARED
  init.cc
)
set_target_properties(cyber_init  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_init
  cyber::binary
  cyber::state
  cyber::common::file
  cyber::logger::async_logger
  cyber::node::node
  cyber::proto::clock_cc_proto
  cyber::sysmo::sysmo
  cyber::time::clock
  cyber::timer::timing_wheel
)
add_library(cyber::init  ALIAS   cyber_init)

add_library(cyber_cyber_core  SHARED
  cyber.cc
)
set_target_properties(cyber_cyber_core  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_cyber_core
  cyber::binary
  cyber::init
  cyber::state
  cyber::base::base
  cyber::blocker::blocker_manager
  cyber::class_loader::class_loader
  cyber::class_loader::class_loader_manager
  cyber::common::common
  cyber::component::component
  cyber::component::timer_component
  cyber::croutine::croutine
  cyber::data::data
  cyber::event::perf_event_cache
  cyber::io::io
  cyber::logger::logger
  cyber::logger::async_logger
  cyber::message::message_traits
  cyber::message::protobuf_traits
  cyber::message::py_message_traits
  cyber::message::raw_message_traits
  cyber::node::node
  cyber::parameter::parameter_client
  cyber::parameter::parameter_server
  cyber::proto::run_mode_conf_cc_proto
  cyber::record::record
  cyber::scheduler::scheduler
  cyber::scheduler::scheduler_factory
  cyber::service::service
  cyber::service::client
  cyber::service_discovery::topology_manager
  cyber::sysmo::sysmo
  cyber::task::task
  cyber::time::time
  cyber::time::clock
  cyber::time::duration
  cyber::time::rate
  cyber::timer::timer
  cyber::transport::transport
  cyber::transport::rtps::participant
  cyber::transport::rtps::sub_listener
  -lrt
  ${glog_LIBRARIES}
  ${Protobuf_LIBRARIES}
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::cyber_core  ALIAS   cyber_cyber_core)

