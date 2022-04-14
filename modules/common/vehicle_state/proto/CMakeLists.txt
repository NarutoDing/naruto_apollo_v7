cmake_minimum_required(VERSION 3.16)

project(modules_common_vehicle_state_proto)
message("${Green} [info] modules_common_vehicle_state_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/common/vehicle_state/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_common_vehicle_state_proto_vehicle_state_cc_proto  SHARED
  vehicle_state.pb.cc
)
set_target_properties(modules_common_vehicle_state_proto_vehicle_state_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_vehicle_state_proto_vehicle_state_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::localization::proto::pose_cc_proto
)
add_library(modules::common::vehicle_state::proto::vehicle_state_cc_proto  ALIAS   modules_common_vehicle_state_proto_vehicle_state_cc_proto)

