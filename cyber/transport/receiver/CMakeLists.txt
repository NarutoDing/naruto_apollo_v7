cmake_minimum_required(VERSION 3.16)

project(cyber_transport_receiver)
message("${Green} [info] cyber_transport_receiver cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_receiver_receiver  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_transport_receiver_receiver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_receiver_receiver
  cyber::transport::receiver::hybrid_receiver
  cyber::transport::receiver::intra_receiver
  cyber::transport::receiver::rtps_receiver
  cyber::transport::receiver::shm_receiver
)
add_library(cyber::transport::receiver::receiver  ALIAS   cyber_transport_receiver_receiver)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_receiver_receiver_interface  SHARED
  ${virtual_cc}
  receiver.h
)
set_target_properties(cyber_transport_receiver_receiver_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_receiver_receiver_interface
  cyber::transport::common::endpoint
  cyber::transport::message::history
  cyber::transport::message::message_info
)
add_library(cyber::transport::receiver::receiver_interface  ALIAS   cyber_transport_receiver_receiver_interface)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_receiver_hybrid_receiver  SHARED
  ${virtual_cc}
  hybrid_receiver.h
)
set_target_properties(cyber_transport_receiver_hybrid_receiver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_receiver_hybrid_receiver
  cyber::transport::receiver::receiver_interface
)
add_library(cyber::transport::receiver::hybrid_receiver  ALIAS   cyber_transport_receiver_hybrid_receiver)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_receiver_intra_receiver  SHARED
  ${virtual_cc}
  intra_receiver.h
)
set_target_properties(cyber_transport_receiver_intra_receiver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_receiver_intra_receiver
  cyber::transport::receiver::receiver_interface
)
add_library(cyber::transport::receiver::intra_receiver  ALIAS   cyber_transport_receiver_intra_receiver)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_receiver_rtps_receiver  SHARED
  ${virtual_cc}
  rtps_receiver.h
)
set_target_properties(cyber_transport_receiver_rtps_receiver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_receiver_rtps_receiver
  cyber::transport::receiver::receiver_interface
)
add_library(cyber::transport::receiver::rtps_receiver  ALIAS   cyber_transport_receiver_rtps_receiver)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_receiver_shm_receiver  SHARED
  ${virtual_cc}
  shm_receiver.h
)
set_target_properties(cyber_transport_receiver_shm_receiver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_receiver_shm_receiver
  cyber::transport::receiver::receiver_interface
  cyber::transport::shm::readable_info
)
add_library(cyber::transport::receiver::shm_receiver  ALIAS   cyber_transport_receiver_shm_receiver)

