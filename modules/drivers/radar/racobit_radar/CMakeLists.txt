cmake_minimum_required(VERSION 3.16)

project(modules_drivers_radar_racobit_radar)
message("${Green} [info] modules_drivers_radar_racobit_radar cmakelist ${ColourReset}")

add_library(modules_drivers_radar_racobit_radar_racobit_radar_message_manager  SHARED
  racobit_radar_message_manager.cc
)
set_target_properties(modules_drivers_radar_racobit_radar_racobit_radar_message_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_radar_racobit_radar_racobit_radar_message_manager
  modules::common::util::message_util
  modules::drivers::canbus::sensor_gflags
  modules::drivers::canbus::can_client::can_client_factory
  modules::drivers::canbus::can_comm::can_sender
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::proto::racobit_radar_cc_proto
  modules::drivers::radar::racobit_radar::protocol::drivers_racobit_radar_protocol
)
add_library(modules::drivers::radar::racobit_radar::racobit_radar_message_manager  ALIAS   modules_drivers_radar_racobit_radar_racobit_radar_message_manager)

add_library(modules_drivers_radar_racobit_radar_racobit_radar_canbus_lib  SHARED
  racobit_radar_canbus_component.cc
)
set_target_properties(modules_drivers_radar_racobit_radar_racobit_radar_canbus_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_radar_racobit_radar_racobit_radar_canbus_lib
  modules::drivers::radar::racobit_radar::racobit_radar_message_manager
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::drivers::canbus::sensor_gflags
  modules::drivers::canbus::can_client::can_client_factory
  modules::drivers::canbus::can_comm::can_receiver
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::proto::sensor_canbus_conf_cc_proto
  modules::drivers::radar::racobit_radar::protocol::drivers_racobit_radar_protocol
)
add_library(modules::drivers::radar::racobit_radar::racobit_radar_canbus_lib  ALIAS   modules_drivers_radar_racobit_radar_racobit_radar_canbus_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libracobit_radar_canbus_component  SHARED
  ${virtual_cc}
)
set_target_properties(libracobit_radar_canbus_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libracobit_radar_canbus_component
  modules::drivers::radar::racobit_radar::racobit_radar_canbus_lib
)
