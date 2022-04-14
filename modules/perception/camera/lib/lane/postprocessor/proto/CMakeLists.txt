cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_lane_postprocessor_proto)
message("${Green} [info] modules_perception_camera_lib_lane_postprocessor_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/perception/camera/lib/lane/postprocessor/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

