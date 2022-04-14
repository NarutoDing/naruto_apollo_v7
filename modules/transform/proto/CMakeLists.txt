cmake_minimum_required(VERSION 3.16)

project(modules_transform_proto)
message("${Green} [info] modules_transform_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/transform/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_transform_proto_static_transform_conf_cc_proto  SHARED
  static_transform_conf.pb.cc
)
set_target_properties(modules_transform_proto_static_transform_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::transform::proto::static_transform_conf_cc_proto  ALIAS   modules_transform_proto_static_transform_conf_cc_proto)

add_library(modules_transform_proto_transform_cc_proto  SHARED
  transform.pb.cc
)
set_target_properties(modules_transform_proto_transform_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_transform_proto_transform_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::transform::proto::transform_cc_proto  ALIAS   modules_transform_proto_transform_cc_proto)

