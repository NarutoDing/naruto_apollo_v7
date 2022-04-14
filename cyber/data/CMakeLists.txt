cmake_minimum_required(VERSION 3.16)

project(cyber_data)
message("${Green} [info] cyber_data cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_data_data  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_data_data  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_data_data
  cyber::data::all_latest
  cyber::data::cache_buffer
  cyber::data::channel_buffer
  cyber::data::data_dispatcher
  cyber::data::data_fusion
  cyber::data::data_notifier
  cyber::data::data_visitor
  cyber::data::data_visitor_base
)
add_library(cyber::data::data  ALIAS   cyber_data_data)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_data_cache_buffer  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_data_cache_buffer  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::data::cache_buffer  ALIAS   cyber_data_cache_buffer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_data_channel_buffer  SHARED
  ${virtual_cc}
  channel_buffer.h
)
set_target_properties(cyber_data_channel_buffer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_data_channel_buffer
  cyber::data::data_notifier
  cyber::proto::component_conf_cc_proto
)
add_library(cyber::data::channel_buffer  ALIAS   cyber_data_channel_buffer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_data_data_dispatcher  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_data_data_dispatcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_data_data_dispatcher
  cyber::data::channel_buffer
)
add_library(cyber::data::data_dispatcher  ALIAS   cyber_data_data_dispatcher)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_data_data_visitor  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_data_data_visitor  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::data::data_visitor  ALIAS   cyber_data_data_visitor)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_data_data_visitor_base  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_data_data_visitor_base  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::data::data_visitor_base  ALIAS   cyber_data_data_visitor_base)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_data_data_notifier  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_data_data_notifier  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_data_data_notifier
  cyber::data::cache_buffer
)
add_library(cyber::data::data_notifier  ALIAS   cyber_data_data_notifier)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_data_data_fusion  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_data_data_fusion  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::data::data_fusion  ALIAS   cyber_data_data_fusion)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_data_all_latest  SHARED
  ${virtual_cc}
  fusion/all_latest.h
)
set_target_properties(cyber_data_all_latest  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_data_all_latest
  cyber::data::channel_buffer
  cyber::data::data_fusion
)
add_library(cyber::data::all_latest  ALIAS   cyber_data_all_latest)

