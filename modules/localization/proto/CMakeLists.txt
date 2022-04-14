cmake_minimum_required(VERSION 3.16)

project(modules_localization_proto)
message("${Green} [info] modules_localization_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/localization/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_localization_proto_pose_cc_proto  SHARED
  pose.pb.cc
)
set_target_properties(modules_localization_proto_pose_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_proto_pose_cc_proto
  modules::common::proto::geometry_cc_proto
)
add_library(modules::localization::proto::pose_cc_proto  ALIAS   modules_localization_proto_pose_cc_proto)

add_library(modules_localization_proto_gnss_pnt_result_cc_proto  SHARED
  gnss_pnt_result.pb.cc
)
set_target_properties(modules_localization_proto_gnss_pnt_result_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_proto_gnss_pnt_result_cc_proto
  modules::drivers::gnss::proto::gnss_raw_observation_cc_proto
)
add_library(modules::localization::proto::gnss_pnt_result_cc_proto  ALIAS   modules_localization_proto_gnss_pnt_result_cc_proto)

add_library(modules_localization_proto_localization_status_cc_proto  SHARED
  localization_status.pb.cc
)
set_target_properties(modules_localization_proto_localization_status_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::localization::proto::localization_status_cc_proto  ALIAS   modules_localization_proto_localization_status_cc_proto)

add_library(modules_localization_proto_localization_config_cc_proto  SHARED
  localization_config.pb.cc
)
set_target_properties(modules_localization_proto_localization_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::localization::proto::localization_config_cc_proto  ALIAS   modules_localization_proto_localization_config_cc_proto)

add_library(modules_localization_proto_imu_cc_proto  SHARED
  imu.pb.cc
)
set_target_properties(modules_localization_proto_imu_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_proto_imu_cc_proto
  modules::localization::proto::pose_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::localization::proto::imu_cc_proto  ALIAS   modules_localization_proto_imu_cc_proto)

add_library(modules_localization_proto_localization_cc_proto  SHARED
  localization.pb.cc
)
set_target_properties(modules_localization_proto_localization_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_proto_localization_cc_proto
  modules::localization::proto::localization_status_cc_proto
  modules::localization::proto::pose_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::localization::proto::localization_cc_proto  ALIAS   modules_localization_proto_localization_cc_proto)

add_library(modules_localization_proto_rtk_config_cc_proto  SHARED
  rtk_config.pb.cc
)
set_target_properties(modules_localization_proto_rtk_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::localization::proto::rtk_config_cc_proto  ALIAS   modules_localization_proto_rtk_config_cc_proto)

add_library(modules_localization_proto_gps_cc_proto  SHARED
  gps.pb.cc
)
set_target_properties(modules_localization_proto_gps_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_proto_gps_cc_proto
  modules::localization::proto::pose_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::localization::proto::gps_cc_proto  ALIAS   modules_localization_proto_gps_cc_proto)

add_library(modules_localization_proto_measure_cc_proto  SHARED
  measure.pb.cc
)
set_target_properties(modules_localization_proto_measure_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_proto_measure_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::localization::proto::measure_cc_proto  ALIAS   modules_localization_proto_measure_cc_proto)

add_library(modules_localization_proto_sins_pva_cc_proto  SHARED
  sins_pva.pb.cc
)
set_target_properties(modules_localization_proto_sins_pva_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_proto_sins_pva_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::localization::proto::sins_pva_cc_proto  ALIAS   modules_localization_proto_sins_pva_cc_proto)

