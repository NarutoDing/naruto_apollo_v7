cmake_minimum_required(VERSION 3.16)

project(modules_localization_rtk)
message("${Green} [info] modules_localization_rtk cmakelist ${ColourReset}")

add_library(modules_localization_rtk_rtk_localization_component_lib  SHARED
  rtk_localization.cc
  rtk_localization_component.cc
)
set_target_properties(modules_localization_rtk_rtk_localization_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_rtk_rtk_localization_component_lib
  cyber::cyber
  cyber::time::clock
  modules::common::math::math
  modules::common::monitor_log::monitor_log
  modules::common::proto::geometry_cc_proto
  modules::common::util::message_util
  modules::common::util::string_util
  modules::drivers::gnss::proto::gnss_best_pose_cc_proto
  modules::drivers::gnss::proto::gnss_cc_proto
  modules::drivers::gnss::proto::ins_cc_proto
  modules::localization::proto::gps_cc_proto
  modules::localization::proto::imu_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::localization::proto::rtk_config_cc_proto
  modules::transform::transform_broadcaster
  
  ${eigen}
)
add_library(modules::localization::rtk::rtk_localization_component_lib  ALIAS   modules_localization_rtk_rtk_localization_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(librtk_localization_component  SHARED
  ${virtual_cc}
)
set_target_properties(librtk_localization_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(librtk_localization_component
  modules::localization::rtk::rtk_localization_component_lib
)
