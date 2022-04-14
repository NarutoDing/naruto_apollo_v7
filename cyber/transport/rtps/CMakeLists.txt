cmake_minimum_required(VERSION 3.16)

project(cyber_transport_rtps)
message("${Green} [info] cyber_transport_rtps cmakelist ${ColourReset}")

add_library(cyber_transport_rtps_attributes_filler  SHARED
  attributes_filler.cc
)
set_target_properties(cyber_transport_rtps_attributes_filler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_rtps_attributes_filler
  cyber::common::log
  cyber::transport::qos::qos
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::transport::rtps::attributes_filler  ALIAS   cyber_transport_rtps_attributes_filler)

add_library(cyber_transport_rtps_underlay_message  SHARED
  underlay_message.cc
)
set_target_properties(cyber_transport_rtps_underlay_message  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_rtps_underlay_message
  cyber::common::log
  ${fastcdr_LIB_DIR}/libfastcdr.so
)
add_library(cyber::transport::rtps::underlay_message  ALIAS   cyber_transport_rtps_underlay_message)

add_library(cyber_transport_rtps_participant  SHARED
  participant.cc
)
set_target_properties(cyber_transport_rtps_participant  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_rtps_participant
  cyber::transport::rtps::underlay_message
  cyber::transport::rtps::underlay_message_type
  cyber::common::global_data
)
add_library(cyber::transport::rtps::participant  ALIAS   cyber_transport_rtps_participant)

add_library(cyber_transport_rtps_sub_listener  SHARED
  sub_listener.cc
)
set_target_properties(cyber_transport_rtps_sub_listener  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_rtps_sub_listener
  cyber::transport::rtps::underlay_message
  cyber::transport::rtps::underlay_message_type
  cyber::transport::message::message_info
)
add_library(cyber::transport::rtps::sub_listener  ALIAS   cyber_transport_rtps_sub_listener)

add_library(cyber_transport_rtps_underlay_message_type  SHARED
  underlay_message_type.cc
)
set_target_properties(cyber_transport_rtps_underlay_message_type  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_rtps_underlay_message_type
  cyber::transport::rtps::underlay_message
  ${fastcdr_LIB_DIR}/libfastcdr.so
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::transport::rtps::underlay_message_type  ALIAS   cyber_transport_rtps_underlay_message_type)

