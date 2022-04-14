cmake_minimum_required(VERSION 3.16)

project(modules_map_tools_map_datachecker_proto)
message("${Green} [info] modules_map_tools_map_datachecker_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/map/tools/map_datachecker/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_map_tools_map_datachecker_proto_collection_service_cc_proto  SHARED
  collection_service.pb.cc
)
set_target_properties(modules_map_tools_map_datachecker_proto_collection_service_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_proto_collection_service_cc_proto
  modules::map::tools::map_datachecker::proto::collection_check_message_cc_proto
)
add_library(modules::map::tools::map_datachecker::proto::collection_service_cc_proto  ALIAS   modules_map_tools_map_datachecker_proto_collection_service_cc_proto)

add_library(modules_map_tools_map_datachecker_proto_collection_check_message_cc_proto  SHARED
  collection_check_message.pb.cc
)
set_target_properties(modules_map_tools_map_datachecker_proto_collection_check_message_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_proto_collection_check_message_cc_proto
  modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto
)
add_library(modules::map::tools::map_datachecker::proto::collection_check_message_cc_proto  ALIAS   modules_map_tools_map_datachecker_proto_collection_check_message_cc_proto)

add_library(modules_map_tools_map_datachecker_proto_collection_error_code_cc_proto  SHARED
  collection_error_code.pb.cc
)
set_target_properties(modules_map_tools_map_datachecker_proto_collection_error_code_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto  ALIAS   modules_map_tools_map_datachecker_proto_collection_error_code_cc_proto)

