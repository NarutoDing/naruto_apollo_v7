cmake_minimum_required(VERSION 3.16)

project(cyber_transport_transmitter)
message("${Green} [info] cyber_transport_transmitter cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_transmitter_transmitter  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_transport_transmitter_transmitter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_transmitter_transmitter
  cyber::transport::transmitter::hybrid_transmitter
  cyber::transport::transmitter::intra_transmitter
  cyber::transport::transmitter::rtps_transmitter
  cyber::transport::transmitter::shm_transmitter
)
add_library(cyber::transport::transmitter::transmitter  ALIAS   cyber_transport_transmitter_transmitter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_transmitter_hybrid_transmitter  SHARED
  ${virtual_cc}
  hybrid_transmitter.h
)
set_target_properties(cyber_transport_transmitter_hybrid_transmitter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_transmitter_hybrid_transmitter
  cyber::transport::transmitter::transmitter_interface
)
add_library(cyber::transport::transmitter::hybrid_transmitter  ALIAS   cyber_transport_transmitter_hybrid_transmitter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_transmitter_intra_transmitter  SHARED
  ${virtual_cc}
  intra_transmitter.h
)
set_target_properties(cyber_transport_transmitter_intra_transmitter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_transmitter_intra_transmitter
  cyber::transport::transmitter::transmitter_interface
)
add_library(cyber::transport::transmitter::intra_transmitter  ALIAS   cyber_transport_transmitter_intra_transmitter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_transmitter_transmitter_interface  SHARED
  ${virtual_cc}
  transmitter.h
)
set_target_properties(cyber_transport_transmitter_transmitter_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_transmitter_transmitter_interface
  cyber::event::perf_event_cache
  cyber::transport::common::endpoint
  cyber::transport::message::message_info
)
add_library(cyber::transport::transmitter::transmitter_interface  ALIAS   cyber_transport_transmitter_transmitter_interface)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_transmitter_rtps_transmitter  SHARED
  ${virtual_cc}
  rtps_transmitter.h
)
set_target_properties(cyber_transport_transmitter_rtps_transmitter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_transmitter_rtps_transmitter
  cyber::transport::transmitter::transmitter_interface
)
add_library(cyber::transport::transmitter::rtps_transmitter  ALIAS   cyber_transport_transmitter_rtps_transmitter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_transmitter_shm_transmitter  SHARED
  ${virtual_cc}
  shm_transmitter.h
)
set_target_properties(cyber_transport_transmitter_shm_transmitter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_transmitter_shm_transmitter
  cyber::transport::transmitter::transmitter_interface
)
add_library(cyber::transport::transmitter::shm_transmitter  ALIAS   cyber_transport_transmitter_shm_transmitter)

