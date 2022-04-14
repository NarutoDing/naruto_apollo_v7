cmake_minimum_required(VERSION 3.16)

project(modules_guardian)
message("${Green} [info] modules_guardian cmakelist ${ColourReset}")

add_library(modules_guardian_guardian_component_lib  SHARED
  guardian_component.cc
)
set_target_properties(modules_guardian_guardian_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_guardian_guardian_component_lib
  cyber::cyber
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::control::proto::control_cmd_cc_proto
  modules::guardian::proto::guardian_cc_proto
  modules::guardian::proto::guardian_conf_cc_proto
  modules::monitor::proto::system_status_cc_proto
)
add_library(modules::guardian::guardian_component_lib  ALIAS   modules_guardian_guardian_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libguardian_component  SHARED
  ${virtual_cc}
)
set_target_properties(libguardian_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libguardian_component
  modules::guardian::guardian_component_lib
)
