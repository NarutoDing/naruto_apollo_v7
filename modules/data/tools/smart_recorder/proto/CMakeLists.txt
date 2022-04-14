cmake_minimum_required(VERSION 3.16)

project(modules_data_tools_smart_recorder_proto)
message("${Green} [info] modules_data_tools_smart_recorder_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/data/tools/smart_recorder/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_data_tools_smart_recorder_proto_smart_recorder_triggers_cc_proto  SHARED
  smart_recorder_triggers.pb.cc
)
set_target_properties(modules_data_tools_smart_recorder_proto_smart_recorder_triggers_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::data::tools::smart_recorder::proto::smart_recorder_triggers_cc_proto  ALIAS   modules_data_tools_smart_recorder_proto_smart_recorder_triggers_cc_proto)

add_library(modules_data_tools_smart_recorder_proto_smart_recorder_status_cc_proto  SHARED
  smart_recorder_status.pb.cc
)
set_target_properties(modules_data_tools_smart_recorder_proto_smart_recorder_status_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_proto_smart_recorder_status_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::data::tools::smart_recorder::proto::smart_recorder_status_cc_proto  ALIAS   modules_data_tools_smart_recorder_proto_smart_recorder_status_cc_proto)

