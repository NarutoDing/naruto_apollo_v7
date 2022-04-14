cmake_minimum_required(VERSION 3.16)

project(cyber_tools_cyber_recorder)
message("${Green} [info] cyber_tools_cyber_recorder cmakelist ${ColourReset}")

add_library(cyber_tools_cyber_recorder_info  SHARED
  info.cc
)
set_target_properties(cyber_tools_cyber_recorder_info  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_recorder_info
  cyber::common::time_conversion
  cyber::proto::record_cc_proto
  cyber::record::record_file_reader
  cyber::record::record_message
)
add_library(cyber::tools::cyber_recorder::info  ALIAS   cyber_tools_cyber_recorder_info)

add_library(cyber_tools_cyber_recorder_recorder  SHARED
  recorder.cc
)
set_target_properties(cyber_tools_cyber_recorder_recorder  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_recorder_recorder
  cyber::cyber
  cyber::common::log
  cyber::proto::record_cc_proto
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::tools::cyber_recorder::recorder  ALIAS   cyber_tools_cyber_recorder_recorder)

add_library(cyber_tools_cyber_recorder_recoverer  SHARED
  recoverer.cc
)
set_target_properties(cyber_tools_cyber_recorder_recoverer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_recorder_recoverer
  cyber::base::for_each
  cyber::common::log
  cyber::proto::record_cc_proto
  cyber::record::header_builder
  cyber::record::record_file_reader
  cyber::record::record_writer
)
add_library(cyber::tools::cyber_recorder::recoverer  ALIAS   cyber_tools_cyber_recorder_recoverer)

add_library(cyber_tools_cyber_recorder_spliter  SHARED
  spliter.cc
)
set_target_properties(cyber_tools_cyber_recorder_spliter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_recorder_spliter
  cyber::common::log
  cyber::proto::record_cc_proto
  cyber::record::header_builder
  cyber::record::record_file_reader
  cyber::record::record_writer
)
add_library(cyber::tools::cyber_recorder::spliter  ALIAS   cyber_tools_cyber_recorder_spliter)

add_executable(cyber_recorder
  main.cc
)
target_link_libraries(cyber_recorder
  cyber::tools::cyber_recorder::info
  cyber::tools::cyber_recorder::recorder
  cyber::tools::cyber_recorder::recoverer
  cyber::tools::cyber_recorder::spliter
  cyber::init
  cyber::common::file
  cyber::common::time_conversion
  cyber::tools::cyber_recorder::player::player
)
