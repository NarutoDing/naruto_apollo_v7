cmake_minimum_required(VERSION 3.16)

project(cyber_service_discovery_communication)
message("${Green} [info] cyber_service_discovery_communication cmakelist ${ColourReset}")

add_library(cyber_service_discovery_communication_participant_listener  SHARED
  participant_listener.cc
)
set_target_properties(cyber_service_discovery_communication_participant_listener  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_communication_participant_listener
  cyber::common::log
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::service_discovery::communication::participant_listener  ALIAS   cyber_service_discovery_communication_participant_listener)

add_library(cyber_service_discovery_communication_subscriber_listener  SHARED
  subscriber_listener.cc
)
set_target_properties(cyber_service_discovery_communication_subscriber_listener  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_communication_subscriber_listener
  cyber::common::log
  cyber::transport::rtps::underlay_message
  cyber::transport::rtps::underlay_message_type
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::service_discovery::communication::subscriber_listener  ALIAS   cyber_service_discovery_communication_subscriber_listener)

