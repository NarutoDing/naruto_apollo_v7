cmake_minimum_required(VERSION 3.16)

project(modules_drivers_tools_image_decompress_proto)
message("${Green} [info] modules_drivers_tools_image_decompress_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/drivers/tools/image_decompress/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_drivers_tools_image_decompress_proto_config_cc_proto  SHARED
  config.pb.cc
)
set_target_properties(modules_drivers_tools_image_decompress_proto_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::tools::image_decompress::proto::config_cc_proto  ALIAS   modules_drivers_tools_image_decompress_proto_config_cc_proto)

