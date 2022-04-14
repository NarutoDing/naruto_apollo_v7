cmake_minimum_required(VERSION 3.16)

project(modules_common_configs_proto)
message("${Green} [info] modules_common_configs_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/common/configs/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_common_configs_proto_vehicle_config_cc_proto  SHARED
  vehicle_config.pb.cc
)
set_target_properties(modules_common_configs_proto_vehicle_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_configs_proto_vehicle_config_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::common::configs::proto::vehicle_config_cc_proto  ALIAS   modules_common_configs_proto_vehicle_config_cc_proto)

