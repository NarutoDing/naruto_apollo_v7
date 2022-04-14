cmake_minimum_required(VERSION 3.16)

project(modules_drivers_gnss)
message("${Green} [info] modules_drivers_gnss cmakelist ${ColourReset}")

add_library(modules_drivers_gnss_gnss_component_lib  SHARED
  gnss_component.cc
)
set_target_properties(modules_drivers_gnss_gnss_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_gnss_gnss_component_lib
  cyber::cyber
  modules::canbus::proto::chassis_cc_proto
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::monitor_log::monitor_log
  modules::common::proto::drive_state_cc_proto
  modules::common::proto::vehicle_signal_cc_proto
  modules::drivers::gnss::proto::gnss_status_cc_proto
  modules::drivers::gnss::proto::ins_cc_proto
  modules::drivers::gnss::stream::gnss_stream
)
add_library(modules::drivers::gnss::gnss_component_lib  ALIAS   modules_drivers_gnss_gnss_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libgnss_component  SHARED
  ${virtual_cc}
)
set_target_properties(libgnss_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libgnss_component
  modules::drivers::gnss::gnss_component_lib
)
