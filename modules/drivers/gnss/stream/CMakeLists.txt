cmake_minimum_required(VERSION 3.16)

project(modules_drivers_gnss_stream)
message("${Green} [info] modules_drivers_gnss_stream cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_gnss_stream_gnss_stream  SHARED
  ${virtual_cc}
)
set_target_properties(modules_drivers_gnss_stream_gnss_stream  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_stream_gnss_stream
  modules::drivers::gnss::stream::ntrip_stream
  modules::drivers::gnss::stream::raw_stream
  modules::drivers::gnss::stream::serial_stream
  modules::drivers::gnss::stream::tcp_stream
  modules::drivers::gnss::stream::udp_stream
)
add_library(modules::drivers::gnss::stream::gnss_stream  ALIAS   modules_drivers_gnss_stream_gnss_stream)

add_library(modules_drivers_gnss_stream_ntrip_stream  SHARED
  ntrip_stream.cc
)
set_target_properties(modules_drivers_gnss_stream_ntrip_stream  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_stream_ntrip_stream
  modules::drivers::gnss::stream::stream
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::math::math
  modules::common::proto::pnc_point_cc_proto
  modules::common::util::util
)
add_library(modules::drivers::gnss::stream::ntrip_stream  ALIAS   modules_drivers_gnss_stream_ntrip_stream)

add_library(modules_drivers_gnss_stream_raw_stream  SHARED
  raw_stream.cc
)
set_target_properties(modules_drivers_gnss_stream_raw_stream  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_stream_raw_stream
  modules::drivers::gnss::stream::ntrip_stream
  modules::drivers::gnss::stream::serial_stream
  modules::drivers::gnss::stream::stream
  cyber::cyber
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::proto::drive_state_cc_proto
  modules::common::proto::vehicle_signal_cc_proto
  modules::common::util::message_util
  modules::drivers::gnss::parser::gnss_parser
  modules::drivers::gnss::proto::gnss_status_cc_proto
  modules::drivers::gnss::proto::heading_cc_proto
  modules::drivers::gnss::proto::imu_cc_proto
  modules::drivers::gnss::util::gnss_util
  ${absl}
)
add_library(modules::drivers::gnss::stream::raw_stream  ALIAS   modules_drivers_gnss_stream_raw_stream)

add_library(modules_drivers_gnss_stream_serial_stream  SHARED
  serial_stream.cc
)
set_target_properties(modules_drivers_gnss_stream_serial_stream  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_stream_serial_stream
  modules::drivers::gnss::stream::stream
  cyber::cyber
  modules::drivers::gnss::util::gnss_util
)
add_library(modules::drivers::gnss::stream::serial_stream  ALIAS   modules_drivers_gnss_stream_serial_stream)

add_library(modules_drivers_gnss_stream_tcp_stream  SHARED
  tcp_stream.cc
)
set_target_properties(modules_drivers_gnss_stream_tcp_stream  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_stream_tcp_stream
  modules::drivers::gnss::stream::stream
  cyber::cyber
)
add_library(modules::drivers::gnss::stream::tcp_stream  ALIAS   modules_drivers_gnss_stream_tcp_stream)

add_library(modules_drivers_gnss_stream_udp_stream  SHARED
  udp_stream.cc
)
set_target_properties(modules_drivers_gnss_stream_udp_stream  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_stream_udp_stream
  modules::drivers::gnss::stream::stream
  cyber::cyber
  modules::drivers::gnss::util::gnss_util
)
add_library(modules::drivers::gnss::stream::udp_stream  ALIAS   modules_drivers_gnss_stream_udp_stream)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_gnss_stream_stream  SHARED
  ${virtual_cc}
  stream.h
)
set_target_properties(modules_drivers_gnss_stream_stream  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_stream_stream
  cyber::cyber
  modules::drivers::gnss::util::gnss_util
)
add_library(modules::drivers::gnss::stream::stream  ALIAS   modules_drivers_gnss_stream_stream)

