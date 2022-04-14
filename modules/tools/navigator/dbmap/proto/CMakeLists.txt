cmake_minimum_required(VERSION 3.16)

project(modules_tools_navigator_dbmap_proto)
message("${Green} [info] modules_tools_navigator_dbmap_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/tools/navigator/dbmap/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_tools_navigator_dbmap_proto_dbmap_cc_proto  SHARED
  dbmap.pb.cc
)
set_target_properties(modules_tools_navigator_dbmap_proto_dbmap_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::tools::navigator::dbmap::proto::dbmap_cc_proto  ALIAS   modules_tools_navigator_dbmap_proto_dbmap_cc_proto)

