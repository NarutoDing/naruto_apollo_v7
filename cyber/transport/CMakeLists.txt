cmake_minimum_required(VERSION 3.16)

project(cyber_transport)
message("${Green} [info] cyber_transport cmakelist ${ColourReset}")

add_library(cyber_transport_transport  SHARED
  transport.cc
)
set_target_properties(cyber_transport_transport  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_transport
  cyber::service_discovery::role
  cyber::task::task
  cyber::transport::dispatcher::intra_dispatcher
  cyber::transport::dispatcher::rtps_dispatcher
  cyber::transport::dispatcher::shm_dispatcher
  cyber::transport::message::history
  cyber::transport::qos::qos
  cyber::transport::receiver::receiver
  cyber::transport::rtps::attributes_filler
  cyber::transport::rtps::participant
  cyber::transport::rtps::sub_listener
  cyber::transport::rtps::underlay_message
  cyber::transport::rtps::underlay_message_type
  cyber::transport::transmitter::transmitter
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::transport::transport  ALIAS   cyber_transport_transport)

