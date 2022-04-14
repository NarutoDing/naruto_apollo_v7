cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_traffic_light_proto)
message("${Green} [info] modules_perception_camera_lib_traffic_light_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/perception/camera/lib/traffic_light/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_perception_camera_lib_traffic_light_proto_detection_cc_proto  SHARED
  detection.pb.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_proto_detection_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::camera::lib::traffic_light::proto::detection_cc_proto  ALIAS   modules_perception_camera_lib_traffic_light_proto_detection_cc_proto)

