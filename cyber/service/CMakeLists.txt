cmake_minimum_required(VERSION 3.16)

project(cyber_service)
message("${Green} [info] cyber_service cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_service_client  SHARED
  ${virtual_cc}
  client.h
)
set_target_properties(cyber_service_client  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_client
  cyber::service::client_base
)
add_library(cyber::service::client  ALIAS   cyber_service_client)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_service_client_base  SHARED
  ${virtual_cc}
  client_base.h
)
set_target_properties(cyber_service_client_base  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::service::client_base  ALIAS   cyber_service_client_base)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_service_service  SHARED
  ${virtual_cc}
  service.h
)
set_target_properties(cyber_service_service  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_service
  cyber::service::service_base
  cyber::scheduler::scheduler
)
add_library(cyber::service::service  ALIAS   cyber_service_service)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_service_service_base  SHARED
  ${virtual_cc}
  service_base.h
)
set_target_properties(cyber_service_service_base  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::service::service_base  ALIAS   cyber_service_service_base)

