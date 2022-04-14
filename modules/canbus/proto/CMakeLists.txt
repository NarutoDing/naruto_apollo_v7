cmake_minimum_required(VERSION 3.16)

project(modules_canbus_proto)
message("${Green} [info] modules_canbus_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/canbus/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_canbus_proto_devkit_cc_proto  SHARED
  devkit.pb.cc
)
set_target_properties(modules_canbus_proto_devkit_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::canbus::proto::devkit_cc_proto  ALIAS   modules_canbus_proto_devkit_cc_proto)

add_library(modules_canbus_proto_chassis_cc_proto  SHARED
  chassis.pb.cc
)
set_target_properties(modules_canbus_proto_chassis_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_proto_chassis_cc_proto
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::proto::drive_state_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::proto::vehicle_signal_cc_proto
)
add_library(modules::canbus::proto::chassis_cc_proto  ALIAS   modules_canbus_proto_chassis_cc_proto)

add_library(modules_canbus_proto_ch_cc_proto  SHARED
  ch.pb.cc
)
set_target_properties(modules_canbus_proto_ch_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::canbus::proto::ch_cc_proto  ALIAS   modules_canbus_proto_ch_cc_proto)

add_library(modules_canbus_proto_zhongyun_cc_proto  SHARED
  zhongyun.pb.cc
)
set_target_properties(modules_canbus_proto_zhongyun_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::canbus::proto::zhongyun_cc_proto  ALIAS   modules_canbus_proto_zhongyun_cc_proto)

add_library(modules_canbus_proto_vehicle_parameter_cc_proto  SHARED
  vehicle_parameter.pb.cc
)
set_target_properties(modules_canbus_proto_vehicle_parameter_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_proto_vehicle_parameter_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::configs::proto::vehicle_config_cc_proto
)
add_library(modules::canbus::proto::vehicle_parameter_cc_proto  ALIAS   modules_canbus_proto_vehicle_parameter_cc_proto)

add_library(modules_canbus_proto_lexus_cc_proto  SHARED
  lexus.pb.cc
)
set_target_properties(modules_canbus_proto_lexus_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::canbus::proto::lexus_cc_proto  ALIAS   modules_canbus_proto_lexus_cc_proto)

add_library(modules_canbus_proto_wey_cc_proto  SHARED
  wey.pb.cc
)
set_target_properties(modules_canbus_proto_wey_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::canbus::proto::wey_cc_proto  ALIAS   modules_canbus_proto_wey_cc_proto)

add_library(modules_canbus_proto_canbus_conf_cc_proto  SHARED
  canbus_conf.pb.cc
)
set_target_properties(modules_canbus_proto_canbus_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_proto_canbus_conf_cc_proto
  modules::canbus::proto::vehicle_parameter_cc_proto
  modules::drivers::canbus::proto::can_card_parameter_cc_proto
)
add_library(modules::canbus::proto::canbus_conf_cc_proto  ALIAS   modules_canbus_proto_canbus_conf_cc_proto)

add_library(modules_canbus_proto_transit_cc_proto  SHARED
  transit.pb.cc
)
set_target_properties(modules_canbus_proto_transit_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::canbus::proto::transit_cc_proto  ALIAS   modules_canbus_proto_transit_cc_proto)

add_library(modules_canbus_proto_ge3_cc_proto  SHARED
  ge3.pb.cc
)
set_target_properties(modules_canbus_proto_ge3_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::canbus::proto::ge3_cc_proto  ALIAS   modules_canbus_proto_ge3_cc_proto)

add_library(modules_canbus_proto_neolix_edu_cc_proto  SHARED
  neolix_edu.pb.cc
)
set_target_properties(modules_canbus_proto_neolix_edu_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::canbus::proto::neolix_edu_cc_proto  ALIAS   modules_canbus_proto_neolix_edu_cc_proto)

add_library(modules_canbus_proto_chassis_detail_cc_proto  SHARED
  chassis_detail.pb.cc
)
set_target_properties(modules_canbus_proto_chassis_detail_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_proto_chassis_detail_cc_proto
  modules::canbus::proto::ch_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::canbus::proto::devkit_cc_proto
  modules::canbus::proto::ge3_cc_proto
  modules::canbus::proto::lexus_cc_proto
  modules::canbus::proto::neolix_edu_cc_proto
  modules::canbus::proto::transit_cc_proto
  modules::canbus::proto::wey_cc_proto
  modules::canbus::proto::zhongyun_cc_proto
  modules::common::configs::proto::vehicle_config_cc_proto
)
add_library(modules::canbus::proto::chassis_detail_cc_proto  ALIAS   modules_canbus_proto_chassis_detail_cc_proto)

