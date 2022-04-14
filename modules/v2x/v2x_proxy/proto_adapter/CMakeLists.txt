cmake_minimum_required(VERSION 3.16)

project(modules_v2x_v2x_proxy_proto_adapter)
message("${Green} [info] modules_v2x_v2x_proxy_proto_adapter cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files $ENV{NARUTO_APOLLO_ROOT}/modules/v2x/v2x_proxy/proto_adapter/*.proto)
naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})