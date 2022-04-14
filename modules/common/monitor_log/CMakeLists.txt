cmake_minimum_required(VERSION 3.16)

project(modules_common_monitor_log)
message("${Green} [info] modules_common_monitor_log cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_monitor_log_monitor_log  SHARED
  ${virtual_cc}
)
set_target_properties(modules_common_monitor_log_monitor_log  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_monitor_log_monitor_log
  modules::common::monitor_log::monitor_log_buffer
  modules::common::monitor_log::monitor_logger
  cyber::common::log
)
add_library(modules::common::monitor_log::monitor_log  ALIAS   modules_common_monitor_log_monitor_log)

add_library(modules_common_monitor_log_monitor_logger  SHARED
  monitor_logger.cc
)
set_target_properties(modules_common_monitor_log_monitor_logger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_monitor_log_monitor_logger
  cyber::cyber
  modules::common::monitor_log::proto::monitor_log_cc_proto
  modules::common::util::message_util
  ${absl}
)
add_library(modules::common::monitor_log::monitor_logger  ALIAS   modules_common_monitor_log_monitor_logger)

add_library(modules_common_monitor_log_monitor_log_buffer  SHARED
  monitor_log_buffer.cc
)
set_target_properties(modules_common_monitor_log_monitor_log_buffer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_monitor_log_monitor_log_buffer
  modules::common::monitor_log::monitor_logger
  modules::common::monitor_log::proto::monitor_log_cc_proto
  
)
add_library(modules::common::monitor_log::monitor_log_buffer  ALIAS   modules_common_monitor_log_monitor_log_buffer)

