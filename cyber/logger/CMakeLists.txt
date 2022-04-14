cmake_minimum_required(VERSION 3.16)

project(cyber_logger)
message("${Green} [info] cyber_logger cmakelist ${ColourReset}")

add_library(cyber_logger_logger  SHARED
  logger.cc
)
set_target_properties(cyber_logger_logger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_logger_logger
  cyber::common::common
  cyber::logger::log_file_object
)
add_library(cyber::logger::logger  ALIAS   cyber_logger_logger)

add_library(cyber_logger_async_logger  SHARED
  async_logger.cc
)
set_target_properties(cyber_logger_async_logger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_logger_async_logger
  cyber::base::macros
  cyber::common::common
  cyber::logger::log_file_object
)
add_library(cyber::logger::async_logger  ALIAS   cyber_logger_async_logger)

add_library(cyber_logger_log_file_object  SHARED
  log_file_object.cc
)
set_target_properties(cyber_logger_log_file_object  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_logger_log_file_object
  cyber::binary
  cyber::common::log
  cyber::logger::logger_util
)
add_library(cyber::logger::log_file_object  ALIAS   cyber_logger_log_file_object)

add_library(cyber_logger_logger_util  SHARED
  logger_util.cc
)
set_target_properties(cyber_logger_logger_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_logger_logger_util
  cyber::common::global_data
)
add_library(cyber::logger::logger_util  ALIAS   cyber_logger_logger_util)

