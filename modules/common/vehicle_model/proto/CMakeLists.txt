cmake_minimum_required(VERSION 3.16)

project(modules_common_vehicle_model_proto)
message("${Green} [info] modules_common_vehicle_model_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/common/vehicle_model/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_common_vehicle_model_proto_vehicle_model_config_cc_proto  SHARED
  vehicle_model_config.pb.cc
)
set_target_properties(modules_common_vehicle_model_proto_vehicle_model_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::vehicle_model::proto::vehicle_model_config_cc_proto  ALIAS   modules_common_vehicle_model_proto_vehicle_model_config_cc_proto)

