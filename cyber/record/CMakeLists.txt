cmake_minimum_required(VERSION 3.16)

project(cyber_record)
message("${Green} [info] cyber_record cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_record_record  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_record_record  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_record_record
  cyber::record::record_reader
  cyber::record::record_viewer
  cyber::record::record_writer
)
add_library(cyber::record::record  ALIAS   cyber_record_record)

add_library(cyber_record_record_file_base  SHARED
  file/record_file_base.cc
)
set_target_properties(cyber_record_record_file_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_record_record_file_base
  cyber::common::log
  cyber::proto::record_cc_proto
)
add_library(cyber::record::record_file_base  ALIAS   cyber_record_record_file_base)

add_library(cyber_record_record_file_reader  SHARED
  file/record_file_reader.cc
)
set_target_properties(cyber_record_record_file_reader  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_record_record_file_reader
  cyber::record::record_file_base
  cyber::record::section
  cyber::common::file
  cyber::time::time
  ${Protobuf_LIBRARIES}
)
add_library(cyber::record::record_file_reader  ALIAS   cyber_record_record_file_reader)

add_library(cyber_record_record_file_writer  SHARED
  file/record_file_writer.cc
)
set_target_properties(cyber_record_record_file_writer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_record_record_file_writer
  cyber::record::record_file_base
  cyber::record::section
  cyber::common::file
  cyber::time::time
  ${Protobuf_LIBRARIES}
)
add_library(cyber::record::record_file_writer  ALIAS   cyber_record_record_file_writer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_record_section  SHARED
  ${virtual_cc}
  file/section.h
)
set_target_properties(cyber_record_section  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::record::section  ALIAS   cyber_record_section)

add_library(cyber_record_header_builder  SHARED
  header_builder.cc
)
set_target_properties(cyber_record_header_builder  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_record_header_builder
  cyber::proto::record_cc_proto
)
add_library(cyber::record::header_builder  ALIAS   cyber_record_header_builder)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_record_record_base  SHARED
  ${virtual_cc}
  record_base.h
)
set_target_properties(cyber_record_record_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_record_record_base
  cyber::proto::record_cc_proto
)
add_library(cyber::record::record_base  ALIAS   cyber_record_record_base)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_record_record_message  SHARED
  ${virtual_cc}
  record_message.h
)
set_target_properties(cyber_record_record_message  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::record::record_message  ALIAS   cyber_record_record_message)

add_library(cyber_record_record_reader  SHARED
  record_reader.cc
)
set_target_properties(cyber_record_record_reader  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_record_record_reader
  cyber::record::record_base
  cyber::record::record_file_reader
  cyber::record::record_message
)
add_library(cyber::record::record_reader  ALIAS   cyber_record_record_reader)

add_library(cyber_record_record_viewer  SHARED
  record_viewer.cc
)
set_target_properties(cyber_record_record_viewer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_record_record_viewer
  cyber::record::record_message
  cyber::record::record_reader
)
add_library(cyber::record::record_viewer  ALIAS   cyber_record_record_viewer)

add_library(cyber_record_record_writer  SHARED
  record_writer.cc
)
set_target_properties(cyber_record_record_writer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_record_record_writer
  cyber::record::header_builder
  cyber::record::record_base
  cyber::record::record_file_writer
  cyber::message::message_traits
  cyber::message::raw_message
  cyber::proto::record_cc_proto
)
add_library(cyber::record::record_writer  ALIAS   cyber_record_record_writer)

