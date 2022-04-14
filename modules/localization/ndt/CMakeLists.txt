cmake_minimum_required(VERSION 3.16)

project(modules_localization_ndt)
message("${Green} [info] modules_localization_ndt cmakelist ${ColourReset}")

add_library(modules_localization_ndt_ndt_localization_component_lib  SHARED
  localization_pose_buffer.cc
  ndt_localization.cc
  ndt_localization_component.cc
)
set_target_properties(modules_localization_ndt_ndt_localization_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_ndt_ndt_localization_component_lib
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::math::math
  modules::common::monitor_log::monitor_log
  modules::common::proto::geometry_cc_proto
  modules::common::util::message_util
  modules::common::util::perf_util
  modules::drivers::gnss::proto::gnss_best_pose_cc_proto
  modules::drivers::gnss::proto::gnss_cc_proto
  modules::drivers::gnss::proto::ins_cc_proto
  modules::drivers::proto::pointcloud_cc_proto
  modules::localization::common::localization_common
  modules::localization::msf::common::util::util
  modules::localization::ndt::ndt_locator::ndt_lidar_locator
  modules::localization::proto::gps_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::transform::buffer
  modules::transform::transform_broadcaster
  ${boost}
  ${yaml}
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::ndt::ndt_localization_component_lib  ALIAS   modules_localization_ndt_ndt_localization_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libndt_localization_component  SHARED
  ${virtual_cc}
)
set_target_properties(libndt_localization_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libndt_localization_component
  modules::localization::ndt::ndt_localization_component_lib
)
