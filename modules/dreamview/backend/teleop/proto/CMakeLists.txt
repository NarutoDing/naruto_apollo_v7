cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_teleop_proto)
message("${Green} [info] modules_dreamview_backend_teleop_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/dreamview/backend/teleop/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_dreamview_backend_teleop_proto_daemon_cmd_cc_proto  SHARED
  daemon_cmd.pb.cc
)
set_target_properties(modules_dreamview_backend_teleop_proto_daemon_cmd_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_teleop_proto_daemon_cmd_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::dreamview::backend::teleop::proto::daemon_cmd_cc_proto  ALIAS   modules_dreamview_backend_teleop_proto_daemon_cmd_cc_proto)

add_library(modules_dreamview_backend_teleop_proto_daemon_rpt_cc_proto  SHARED
  daemon_rpt.pb.cc
)
set_target_properties(modules_dreamview_backend_teleop_proto_daemon_rpt_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_teleop_proto_daemon_rpt_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::dreamview::backend::teleop::proto::daemon_rpt_cc_proto  ALIAS   modules_dreamview_backend_teleop_proto_daemon_rpt_cc_proto)

add_library(modules_dreamview_backend_teleop_proto_modem_info_cc_proto  SHARED
  modem_info.pb.cc
)
set_target_properties(modules_dreamview_backend_teleop_proto_modem_info_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_teleop_proto_modem_info_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::dreamview::backend::teleop::proto::modem_info_cc_proto  ALIAS   modules_dreamview_backend_teleop_proto_modem_info_cc_proto)

