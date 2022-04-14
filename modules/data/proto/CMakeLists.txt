cmake_minimum_required(VERSION 3.16)

project(modules_data_proto)
message("${Green} [info] modules_data_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/data/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_data_proto_static_info_cc_proto  SHARED
  static_info.pb.cc
)
set_target_properties(modules_data_proto_static_info_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_proto_static_info_cc_proto
  modules::canbus::proto::canbus_conf_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::control::proto::control_conf_cc_proto
  modules::routing::proto::routing_cc_proto
)
add_library(modules::data::proto::static_info_cc_proto  ALIAS   modules_data_proto_static_info_cc_proto)

add_library(modules_data_proto_frame_cc_proto  SHARED
  frame.pb.cc
)
set_target_properties(modules_data_proto_frame_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::data::proto::frame_cc_proto  ALIAS   modules_data_proto_frame_cc_proto)

