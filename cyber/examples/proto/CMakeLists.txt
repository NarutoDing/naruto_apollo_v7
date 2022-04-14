cmake_minimum_required(VERSION 3.16)

project(cyber_examples_proto)
message("${Green} [info] cyber_examples_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/cyber/examples/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(cyber_examples_proto_examples_cc_proto  SHARED
  examples.pb.cc
)
set_target_properties(cyber_examples_proto_examples_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::examples::proto::examples_cc_proto  ALIAS   cyber_examples_proto_examples_cc_proto)

