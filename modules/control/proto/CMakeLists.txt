cmake_minimum_required(VERSION 3.16)

project(modules_control_proto)
message("${Green} [info] modules_control_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/control/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_control_proto_lon_controller_conf_cc_proto  SHARED
  lon_controller_conf.pb.cc
)
set_target_properties(modules_control_proto_lon_controller_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_lon_controller_conf_cc_proto
  modules::control::proto::calibration_table_cc_proto
  modules::control::proto::leadlag_conf_cc_proto
  modules::control::proto::pid_conf_cc_proto
)
add_library(modules::control::proto::lon_controller_conf_cc_proto  ALIAS   modules_control_proto_lon_controller_conf_cc_proto)

add_library(modules_control_proto_preprocessor_cc_proto  SHARED
  preprocessor.pb.cc
)
set_target_properties(modules_control_proto_preprocessor_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_preprocessor_cc_proto
  modules::control::proto::input_debug_cc_proto
  modules::control::proto::local_view_cc_proto
  modules::common::proto::drive_state_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::control::proto::preprocessor_cc_proto  ALIAS   modules_control_proto_preprocessor_cc_proto)

add_library(modules_control_proto_calibration_table_cc_proto  SHARED
  calibration_table.pb.cc
)
set_target_properties(modules_control_proto_calibration_table_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::control::proto::calibration_table_cc_proto  ALIAS   modules_control_proto_calibration_table_cc_proto)

add_library(modules_control_proto_control_cmd_cc_proto  SHARED
  control_cmd.pb.cc
)
set_target_properties(modules_control_proto_control_cmd_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_control_cmd_cc_proto
  modules::control::proto::input_debug_cc_proto
  modules::control::proto::pad_msg_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::proto::drive_state_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::common::proto::vehicle_signal_cc_proto
)
add_library(modules::control::proto::control_cmd_cc_proto  ALIAS   modules_control_proto_control_cmd_cc_proto)

add_library(modules_control_proto_mpc_controller_conf_cc_proto  SHARED
  mpc_controller_conf.pb.cc
)
set_target_properties(modules_control_proto_mpc_controller_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_mpc_controller_conf_cc_proto
  modules::control::proto::calibration_table_cc_proto
  modules::control::proto::gain_scheduler_conf_cc_proto
)
add_library(modules::control::proto::mpc_controller_conf_cc_proto  ALIAS   modules_control_proto_mpc_controller_conf_cc_proto)

add_library(modules_control_proto_lat_controller_conf_cc_proto  SHARED
  lat_controller_conf.pb.cc
)
set_target_properties(modules_control_proto_lat_controller_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_lat_controller_conf_cc_proto
  modules::control::proto::gain_scheduler_conf_cc_proto
  modules::control::proto::leadlag_conf_cc_proto
  modules::control::proto::mrac_conf_cc_proto
)
add_library(modules::control::proto::lat_controller_conf_cc_proto  ALIAS   modules_control_proto_lat_controller_conf_cc_proto)

add_library(modules_control_proto_gain_scheduler_conf_cc_proto  SHARED
  gain_scheduler_conf.pb.cc
)
set_target_properties(modules_control_proto_gain_scheduler_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::control::proto::gain_scheduler_conf_cc_proto  ALIAS   modules_control_proto_gain_scheduler_conf_cc_proto)

add_library(modules_control_proto_local_view_cc_proto  SHARED
  local_view.pb.cc
)
set_target_properties(modules_control_proto_local_view_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_local_view_cc_proto
  modules::control::proto::pad_msg_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::proto::header_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::planning::proto::planning_cc_proto
)
add_library(modules::control::proto::local_view_cc_proto  ALIAS   modules_control_proto_local_view_cc_proto)

add_library(modules_control_proto_pid_conf_cc_proto  SHARED
  pid_conf.pb.cc
)
set_target_properties(modules_control_proto_pid_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::control::proto::pid_conf_cc_proto  ALIAS   modules_control_proto_pid_conf_cc_proto)

add_library(modules_control_proto_leadlag_conf_cc_proto  SHARED
  leadlag_conf.pb.cc
)
set_target_properties(modules_control_proto_leadlag_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::control::proto::leadlag_conf_cc_proto  ALIAS   modules_control_proto_leadlag_conf_cc_proto)

add_library(modules_control_proto_control_common_conf_cc_proto  SHARED
  control_common_conf.pb.cc
)
set_target_properties(modules_control_proto_control_common_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_control_common_conf_cc_proto
  modules::control::proto::pad_msg_cc_proto
  modules::canbus::proto::chassis_cc_proto
)
add_library(modules::control::proto::control_common_conf_cc_proto  ALIAS   modules_control_proto_control_common_conf_cc_proto)

add_library(modules_control_proto_control_conf_cc_proto  SHARED
  control_conf.pb.cc
)
set_target_properties(modules_control_proto_control_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_control_conf_cc_proto
  modules::control::proto::lat_controller_conf_cc_proto
  modules::control::proto::lon_controller_conf_cc_proto
  modules::control::proto::mpc_controller_conf_cc_proto
  modules::control::proto::pad_msg_cc_proto
  modules::canbus::proto::chassis_cc_proto
)
add_library(modules::control::proto::control_conf_cc_proto  ALIAS   modules_control_proto_control_conf_cc_proto)

add_library(modules_control_proto_input_debug_cc_proto  SHARED
  input_debug.pb.cc
)
set_target_properties(modules_control_proto_input_debug_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_input_debug_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::control::proto::input_debug_cc_proto  ALIAS   modules_control_proto_input_debug_cc_proto)

add_library(modules_control_proto_mrac_conf_cc_proto  SHARED
  mrac_conf.pb.cc
)
set_target_properties(modules_control_proto_mrac_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::control::proto::mrac_conf_cc_proto  ALIAS   modules_control_proto_mrac_conf_cc_proto)

add_library(modules_control_proto_pad_msg_cc_proto  SHARED
  pad_msg.pb.cc
)
set_target_properties(modules_control_proto_pad_msg_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_proto_pad_msg_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::control::proto::pad_msg_cc_proto  ALIAS   modules_control_proto_pad_msg_cc_proto)

