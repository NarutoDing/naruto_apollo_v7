cmake_minimum_required(VERSION 3.16)

project(modules_monitor_hardware)
message("${Green} [info] modules_monitor_hardware cmakelist ${ColourReset}")

add_library(modules_monitor_hardware_gps_monitor  SHARED
  gps_monitor.cc
)
set_target_properties(modules_monitor_hardware_gps_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_hardware_gps_monitor
  cyber::cyber
  modules::drivers::gnss::proto::gnss_best_pose_cc_proto
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
  modules::monitor::software::summary_monitor
)
add_library(modules::monitor::hardware::gps_monitor  ALIAS   modules_monitor_hardware_gps_monitor)

add_library(modules_monitor_hardware_resource_monitor  SHARED
  resource_monitor.cc
)
set_target_properties(modules_monitor_hardware_resource_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_hardware_resource_monitor
  modules::common::util::util
  modules::dreamview::proto::hmi_mode_cc_proto
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
  modules::monitor::software::summary_monitor
  ${boost}
)
add_library(modules::monitor::hardware::resource_monitor  ALIAS   modules_monitor_hardware_resource_monitor)

add_library(modules_monitor_hardware_esdcan_monitor  SHARED
  esdcan_monitor.cc
)
set_target_properties(modules_monitor_hardware_esdcan_monitor  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::monitor::hardware::esdcan_monitor  ALIAS   modules_monitor_hardware_esdcan_monitor)

add_library(modules_monitor_hardware_socket_can_monitor  SHARED
  socket_can_monitor.cc
)
set_target_properties(modules_monitor_hardware_socket_can_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_hardware_socket_can_monitor
  modules::common::util::util
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
  modules::monitor::software::summary_monitor
)
add_library(modules::monitor::hardware::socket_can_monitor  ALIAS   modules_monitor_hardware_socket_can_monitor)

