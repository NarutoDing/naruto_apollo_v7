cmake_minimum_required(VERSION 3.16)

project(modules_monitor_common)
message("${Green} [info] modules_monitor_common cmakelist ${ColourReset}")

add_library(modules_monitor_common_recurrent_runner  SHARED
  recurrent_runner.cc
)
set_target_properties(modules_monitor_common_recurrent_runner  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_common_recurrent_runner
  cyber::cyber
)
add_library(modules::monitor::common::recurrent_runner  ALIAS   modules_monitor_common_recurrent_runner)

add_library(modules_monitor_common_monitor_manager  SHARED
  monitor_manager.cc
)
set_target_properties(modules_monitor_common_monitor_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_common_monitor_manager
  cyber::common::file
  cyber::common::macros
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::monitor_log::monitor_log
  modules::common::proto::drive_event_cc_proto
  modules::common::util::util
  modules::common::util::map_util
  modules::dreamview::backend::common::dreamview_gflags
  modules::dreamview::backend::hmi::hmi_worker
  modules::dreamview::proto::hmi_config_cc_proto
  modules::dreamview::proto::hmi_mode_cc_proto
  modules::dreamview::proto::hmi_status_cc_proto
  modules::localization::proto::pose_cc_proto
  modules::monitor::proto::system_status_cc_proto
  ${gflags_LIBRARIES}
)
add_library(modules::monitor::common::monitor_manager  ALIAS   modules_monitor_common_monitor_manager)

