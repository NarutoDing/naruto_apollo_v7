cmake_minimum_required(VERSION 3.16)

project(cyber_parameter)
message("${Green} [info] cyber_parameter cmakelist ${ColourReset}")

add_library(cyber_parameter_parameter  SHARED
  parameter.cc
)
set_target_properties(cyber_parameter_parameter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_parameter_parameter
  cyber::message::protobuf_factory
  cyber::proto::parameter_cc_proto
)
add_library(cyber::parameter::parameter  ALIAS   cyber_parameter_parameter)

add_library(cyber_parameter_parameter_client  SHARED
  parameter_client.cc
)
set_target_properties(cyber_parameter_parameter_client  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_parameter_parameter_client
  cyber::parameter::parameter
  cyber::parameter::parameter_service_names
  cyber::node::node
  cyber::service::client
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::parameter::parameter_client  ALIAS   cyber_parameter_parameter_client)

add_library(cyber_parameter_parameter_server  SHARED
  parameter_server.cc
)
set_target_properties(cyber_parameter_parameter_server  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_parameter_parameter_server
  cyber::parameter::parameter
  cyber::parameter::parameter_service_names
  cyber::node::node
  cyber::service::service
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::parameter::parameter_server  ALIAS   cyber_parameter_parameter_server)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_parameter_parameter_service_names  SHARED
  ${virtual_cc}
  parameter_service_names.h
)
set_target_properties(cyber_parameter_parameter_service_names  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::parameter::parameter_service_names  ALIAS   cyber_parameter_parameter_service_names)

