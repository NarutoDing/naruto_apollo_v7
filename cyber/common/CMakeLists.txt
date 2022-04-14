cmake_minimum_required(VERSION 3.16)

project(cyber_common)
message("${Green} [info] cyber_common cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_common_common  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_common_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_common_common
  cyber::common::environment
  cyber::common::file
  cyber::common::global_data
  cyber::common::log
  cyber::common::macros
  cyber::common::time_conversion
  cyber::common::types
  cyber::common::util
)
add_library(cyber::common::common  ALIAS   cyber_common_common)

add_library(cyber_common_file  SHARED
  file.cc
)
set_target_properties(cyber_common_file  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_common_file
  cyber::common::log
  ${Protobuf_LIBRARIES}
)
add_library(cyber::common::file  ALIAS   cyber_common_file)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_common_log  SHARED
  ${virtual_cc}
  log.h
)
set_target_properties(cyber_common_log  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_common_log
  cyber::binary
  ${glog_LIBRARIES}
)
add_library(cyber::common::log  ALIAS   cyber_common_log)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_common_environment  SHARED
  ${virtual_cc}
  environment.h
)
set_target_properties(cyber_common_environment  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_common_environment
  cyber::common::log
)
add_library(cyber::common::environment  ALIAS   cyber_common_environment)

add_library(cyber_common_global_data  SHARED
  global_data.cc
)
set_target_properties(cyber_common_global_data  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_common_global_data
  cyber::base::atomic_hash_map
  cyber::base::atomic_rw_lock
  cyber::common::environment
  cyber::common::file
  cyber::common::macros
  cyber::common::util
  cyber::proto::cyber_conf_cc_proto
)
add_library(cyber::common::global_data  ALIAS   cyber_common_global_data)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_common_macros  SHARED
  ${virtual_cc}
  macros.h
)
set_target_properties(cyber_common_macros  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_common_macros
  cyber::base::macros
)
add_library(cyber::common::macros  ALIAS   cyber_common_macros)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_common_time_conversion  SHARED
  ${virtual_cc}
  time_conversion.h
)
set_target_properties(cyber_common_time_conversion  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::common::time_conversion  ALIAS   cyber_common_time_conversion)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_common_types  SHARED
  ${virtual_cc}
  types.h
)
set_target_properties(cyber_common_types  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::common::types  ALIAS   cyber_common_types)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_common_util  SHARED
  ${virtual_cc}
  util.h
)
set_target_properties(cyber_common_util  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::common::util  ALIAS   cyber_common_util)

