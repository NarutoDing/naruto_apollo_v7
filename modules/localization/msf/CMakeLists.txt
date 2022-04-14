cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf)
message("${Green} [info] modules_localization_msf cmakelist ${ColourReset}")

add_library(modules_localization_msf_msf_localization_component_lib  SHARED
  msf_localization.cc
  msf_localization_component.cc
)
set_target_properties(modules_localization_msf_msf_localization_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_msf_localization_component_lib
  cyber::cyber
  cyber::time::clock
  modules::common::adapters::adapter_gflags
  modules::common::math::math
  modules::common::monitor_log::monitor_log
  modules::common::proto::geometry_cc_proto
  modules::common::status::status
  modules::common::util::util
  modules::drivers::gnss::proto::config_cc_proto
  modules::drivers::gnss::proto::gnss_best_pose_cc_proto
  modules::drivers::gnss::proto::gnss_cc_proto
  modules::drivers::gnss::proto::heading_cc_proto
  modules::drivers::gnss::proto::imu_cc_proto
  modules::localization::common::localization_common
  modules::localization::msf::common::util::util
  modules::localization::msf::local_integ::local_integ
  modules::localization::msf::local_pyramid_map::base_map::base_map
  modules::localization::msf::local_pyramid_map::pyramid_map::pyramid_map
  modules::localization::proto::gnss_pnt_result_cc_proto
  modules::localization::proto::gps_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::localization::proto::localization_config_cc_proto
  modules::localization::proto::localization_status_cc_proto
  modules::localization::proto::measure_cc_proto
  modules::localization::proto::sins_pva_cc_proto
  modules::transform::transform_broadcaster
  ${boost}
  ${glog_LIBRARIES}
  ${yaml}
  
)
add_library(modules::localization::msf::msf_localization_component_lib  ALIAS   modules_localization_msf_msf_localization_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libmsf_localization_component  SHARED
  ${virtual_cc}
)
set_target_properties(libmsf_localization_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libmsf_localization_component
  modules::localization::msf::msf_localization_component_lib
)
