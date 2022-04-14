cmake_minimum_required(VERSION 3.16)

project(modules_tools_gen_vehicle_protocol_template)
message("${Green} [info] modules_tools_gen_vehicle_protocol_template cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files $ENV{NARUTO_APOLLO_ROOT}/modules/tools/gen_vehicle_protocol/template/*.proto)
naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})