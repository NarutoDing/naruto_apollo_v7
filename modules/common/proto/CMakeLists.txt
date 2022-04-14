cmake_minimum_required(VERSION 3.16)

project(modules_common_proto)
message("${Green} [info] modules_common_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/common/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_common_proto_error_code_cc_proto  SHARED
  error_code.pb.cc
)
set_target_properties(modules_common_proto_error_code_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::proto::error_code_cc_proto  ALIAS   modules_common_proto_error_code_cc_proto)

add_library(modules_common_proto_drive_state_cc_proto  SHARED
  drive_state.pb.cc
)
set_target_properties(modules_common_proto_drive_state_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::proto::drive_state_cc_proto  ALIAS   modules_common_proto_drive_state_cc_proto)

add_library(modules_common_proto_pnc_point_cc_proto  SHARED
  pnc_point.pb.cc
)
set_target_properties(modules_common_proto_pnc_point_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::proto::pnc_point_cc_proto  ALIAS   modules_common_proto_pnc_point_cc_proto)

add_library(modules_common_proto_geometry_cc_proto  SHARED
  geometry.pb.cc
)
set_target_properties(modules_common_proto_geometry_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::proto::geometry_cc_proto  ALIAS   modules_common_proto_geometry_cc_proto)

add_library(modules_common_proto_direction_cc_proto  SHARED
  direction.pb.cc
)
set_target_properties(modules_common_proto_direction_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::proto::direction_cc_proto  ALIAS   modules_common_proto_direction_cc_proto)

add_library(modules_common_proto_header_cc_proto  SHARED
  header.pb.cc
)
set_target_properties(modules_common_proto_header_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_proto_header_cc_proto
  modules::common::proto::error_code_cc_proto
)
add_library(modules::common::proto::header_cc_proto  ALIAS   modules_common_proto_header_cc_proto)

add_library(modules_common_proto_vehicle_signal_cc_proto  SHARED
  vehicle_signal.pb.cc
)
set_target_properties(modules_common_proto_vehicle_signal_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::proto::vehicle_signal_cc_proto  ALIAS   modules_common_proto_vehicle_signal_cc_proto)

add_library(modules_common_proto_drive_event_cc_proto  SHARED
  drive_event.pb.cc
)
set_target_properties(modules_common_proto_drive_event_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_proto_drive_event_cc_proto
  modules::common::proto::header_cc_proto
  modules::localization::proto::pose_cc_proto
)
add_library(modules::common::proto::drive_event_cc_proto  ALIAS   modules_common_proto_drive_event_cc_proto)

