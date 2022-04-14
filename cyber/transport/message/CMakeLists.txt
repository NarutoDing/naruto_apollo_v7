cmake_minimum_required(VERSION 3.16)

project(cyber_transport_message)
message("${Green} [info] cyber_transport_message cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_message_history_attributes  SHARED
  ${virtual_cc}
  history_attributes.h
)
set_target_properties(cyber_transport_message_history_attributes  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_message_history_attributes
  cyber::proto::qos_profile_cc_proto
)
add_library(cyber::transport::message::history_attributes  ALIAS   cyber_transport_message_history_attributes)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_message_history  SHARED
  ${virtual_cc}
  history.h
)
set_target_properties(cyber_transport_message_history  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_message_history
  cyber::transport::message::history_attributes
)
add_library(cyber::transport::message::history  ALIAS   cyber_transport_message_history)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_message_listener_handler  SHARED
  ${virtual_cc}
  listener_handler.h
)
set_target_properties(cyber_transport_message_listener_handler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_message_listener_handler
  cyber::transport::message::message_info
  cyber::base::signal
  cyber::message::message_traits
  cyber::message::raw_message
)
add_library(cyber::transport::message::listener_handler  ALIAS   cyber_transport_message_listener_handler)

add_library(cyber_transport_message_message_info  SHARED
  message_info.cc
)
set_target_properties(cyber_transport_message_message_info  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_message_message_info
  cyber::common::log
  cyber::transport::common::identity
)
add_library(cyber::transport::message::message_info  ALIAS   cyber_transport_message_message_info)

