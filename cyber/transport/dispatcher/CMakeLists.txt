cmake_minimum_required(VERSION 3.16)

project(cyber_transport_dispatcher)
message("${Green} [info] cyber_transport_dispatcher cmakelist ${ColourReset}")

add_library(cyber_transport_dispatcher_dispatcher  SHARED
  dispatcher.cc
)
set_target_properties(cyber_transport_dispatcher_dispatcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_dispatcher_dispatcher
  cyber::common::common
  cyber::message::message_traits
  cyber::proto::role_attributes_cc_proto
  cyber::transport::message::listener_handler
  cyber::transport::message::message_info
)
add_library(cyber::transport::dispatcher::dispatcher  ALIAS   cyber_transport_dispatcher_dispatcher)

add_library(cyber_transport_dispatcher_intra_dispatcher  SHARED
  intra_dispatcher.cc
)
set_target_properties(cyber_transport_dispatcher_intra_dispatcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_dispatcher_intra_dispatcher
  cyber::transport::dispatcher::dispatcher
  cyber::message::message_traits
  cyber::proto::role_attributes_cc_proto
)
add_library(cyber::transport::dispatcher::intra_dispatcher  ALIAS   cyber_transport_dispatcher_intra_dispatcher)

add_library(cyber_transport_dispatcher_rtps_dispatcher  SHARED
  rtps_dispatcher.cc
)
set_target_properties(cyber_transport_dispatcher_rtps_dispatcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_dispatcher_rtps_dispatcher
  cyber::transport::dispatcher::dispatcher
  cyber::message::message_traits
  cyber::proto::role_attributes_cc_proto
  cyber::transport::rtps::attributes_filler
  cyber::transport::rtps::participant
  cyber::transport::rtps::sub_listener
)
add_library(cyber::transport::dispatcher::rtps_dispatcher  ALIAS   cyber_transport_dispatcher_rtps_dispatcher)

add_library(cyber_transport_dispatcher_shm_dispatcher  SHARED
  shm_dispatcher.cc
)
set_target_properties(cyber_transport_dispatcher_shm_dispatcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_dispatcher_shm_dispatcher
  cyber::transport::dispatcher::dispatcher
  cyber::message::message_traits
  cyber::proto::proto_desc_cc_proto
  cyber::scheduler::scheduler_factory
  cyber::transport::shm::notifier_factory
  cyber::transport::shm::readable_info
  cyber::transport::shm::segment_factory
)
add_library(cyber::transport::dispatcher::shm_dispatcher  ALIAS   cyber_transport_dispatcher_shm_dispatcher)

