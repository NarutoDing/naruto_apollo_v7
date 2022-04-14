cmake_minimum_required(VERSION 3.16)

project(modules_control)
message("${Green} [info] modules_control cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_control_control_lib  SHARED
  ${virtual_cc}
)
set_target_properties(modules_control_control_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_control_lib
  cyber::cyber
  cyber::time::clock
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::latency_recorder::latency_recorder
  modules::common::monitor_log::monitor_log
  modules::common::util::util
  modules::control::common::common
  modules::control::controller::controller
  modules::control::proto::control_cmd_cc_proto
  modules::control::proto::control_conf_cc_proto
  modules::control::proto::pad_msg_cc_proto
  modules::control::proto::preprocessor_cc_proto
  modules::control::submodules::lat_lon_controller_submodule_lib
  modules::control::submodules::mpc_controller_submodule_lib
  modules::control::submodules::postprocessor_submodule_lib
  modules::control::submodules::preprocessor_submodule_lib
  modules::localization::proto::localization_cc_proto
  modules::planning::proto::planning_cc_proto
  ${gflags_LIBRARIES}
)
add_library(modules::control::control_lib  ALIAS   modules_control_control_lib)

add_library(modules_control_control_component_lib  SHARED
  control_component.cc
)
set_target_properties(modules_control_control_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_control_component_lib
  modules::control::control_lib
  modules::control::common::dependency_injector
)
add_library(modules::control::control_component_lib  ALIAS   modules_control_control_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libcontrol_component  SHARED
  ${virtual_cc}
)
set_target_properties(libcontrol_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libcontrol_component
  modules::control::control_component_lib
)
