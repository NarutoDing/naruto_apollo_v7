cmake_minimum_required(VERSION 3.16)

project(modules_canbus_tools)
message("${Green} [info] modules_canbus_tools cmakelist ${ColourReset}")

add_executable(canbus_tester
  canbus_tester.cc
)
target_link_libraries(canbus_tester
  cyber::cyber
  modules::canbus::canbus_component_lib
  modules::canbus::common::canbus_common
  modules::common::adapters::adapter_gflags
  ${gflags_LIBRARIES}
)
add_executable(teleop
  teleop.cc
)
target_link_libraries(teleop
  cyber::cyber
  modules::canbus::common::canbus_common
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::vehicle_controller_base
  modules::common::adapters::adapter_gflags
  modules::common::configs::vehicle_config_helper
  modules::common::util::message_util
  modules::control::proto::control_cmd_cc_proto
  ${gflags_LIBRARIES}
)
