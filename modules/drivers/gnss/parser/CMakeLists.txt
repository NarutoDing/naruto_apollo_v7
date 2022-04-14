cmake_minimum_required(VERSION 3.16)

project(modules_drivers_gnss_parser)
message("${Green} [info] modules_drivers_gnss_parser cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_gnss_parser_gnss_parser  SHARED
  ${virtual_cc}
)
set_target_properties(modules_drivers_gnss_parser_gnss_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_parser_gnss_parser
  modules::drivers::gnss::parser::data_parser
  modules::drivers::gnss::parser::novatel_parser
  modules::drivers::gnss::parser::rtcm_parsers
)
add_library(modules::drivers::gnss::parser::gnss_parser  ALIAS   modules_drivers_gnss_parser_gnss_parser)

add_library(modules_drivers_gnss_parser_data_parser  SHARED
  data_parser.cc
)
set_target_properties(modules_drivers_gnss_parser_data_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_parser_data_parser
  modules::drivers::gnss::parser::novatel_parser
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::drivers::gnss::proto::gnss_best_pose_cc_proto
  modules::drivers::gnss::proto::gnss_cc_proto
  modules::drivers::gnss::proto::gnss_status_cc_proto
  modules::drivers::gnss::util::gnss_util
  modules::localization::proto::gps_cc_proto
  modules::localization::proto::imu_cc_proto
  modules::transform::transform_broadcaster
  ${eigen}
  ${proj}
)
add_library(modules::drivers::gnss::parser::data_parser  ALIAS   modules_drivers_gnss_parser_data_parser)

add_library(modules_drivers_gnss_parser_novatel_parser  SHARED
  novatel_parser.cc
)
set_target_properties(modules_drivers_gnss_parser_novatel_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_parser_novatel_parser
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::proto::error_code_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::drivers::gnss::proto::config_cc_proto
  modules::drivers::gnss::proto::gnss_best_pose_cc_proto
  modules::drivers::gnss::proto::gnss_cc_proto
  modules::drivers::gnss::proto::gnss_raw_observation_cc_proto
  modules::drivers::gnss::proto::heading_cc_proto
  modules::drivers::gnss::proto::imu_cc_proto
  modules::drivers::gnss::proto::ins_cc_proto
  modules::drivers::gnss::util::gnss_util
  third_party::rtklib::rtklib
)
add_library(modules::drivers::gnss::parser::novatel_parser  ALIAS   modules_drivers_gnss_parser_novatel_parser)

add_library(modules_drivers_gnss_parser_rtcm_parsers  SHARED
  rtcm3_parser.cc
  rtcm_parser.cc
)
set_target_properties(modules_drivers_gnss_parser_rtcm_parsers  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_parser_rtcm_parsers
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::drivers::gnss::proto::config_cc_proto
  modules::drivers::gnss::proto::gnss_raw_observation_cc_proto
  modules::drivers::gnss::util::gnss_util
  third_party::rtklib::rtklib
)
add_library(modules::drivers::gnss::parser::rtcm_parsers  ALIAS   modules_drivers_gnss_parser_rtcm_parsers)

