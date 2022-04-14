cmake_minimum_required(VERSION 3.16)

project(modules_monitor)
message("${Green} [info] modules_monitor cmakelist ${ColourReset}")

add_library(modules_monitor_monitor_lib  SHARED
  monitor.cc
)
set_target_properties(modules_monitor_monitor_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_monitor_lib
  cyber::cyber
  modules::common::util::message_util
  modules::monitor::common::recurrent_runner
  modules::monitor::hardware::esdcan_monitor
  modules::monitor::hardware::gps_monitor
  modules::monitor::hardware::resource_monitor
  modules::monitor::hardware::socket_can_monitor
  modules::monitor::software::camera_monitor
  modules::monitor::software::channel_monitor
  modules::monitor::software::functional_safety_monitor
  modules::monitor::software::latency_monitor
  modules::monitor::software::localization_monitor
  modules::monitor::software::module_monitor
  modules::monitor::software::process_monitor
  modules::monitor::software::recorder_monitor
  modules::monitor::software::summary_monitor
)
add_library(modules::monitor::monitor_lib  ALIAS   modules_monitor_monitor_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libmonitor  SHARED
  ${virtual_cc}
)
set_target_properties(libmonitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libmonitor
  modules::monitor::monitor_lib
)
