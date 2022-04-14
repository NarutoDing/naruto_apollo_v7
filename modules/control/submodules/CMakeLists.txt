cmake_minimum_required(VERSION 3.16)

project(modules_control_submodules)
message("${Green} [info] modules_control_submodules cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_control_submodules_control_module_lib  SHARED
  ${virtual_cc}
)
set_target_properties(modules_control_submodules_control_module_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_submodules_control_module_lib
  modules::control::submodules::lat_lon_controller_submodule_lib
  modules::control::submodules::mpc_controller_submodule_lib
  modules::control::submodules::postprocessor_submodule_lib
  modules::control::submodules::preprocessor_submodule_lib
)
add_library(modules::control::submodules::control_module_lib  ALIAS   modules_control_submodules_control_module_lib)

add_library(modules_control_submodules_preprocessor_submodule_lib  SHARED
  preprocessor_submodule.cc
)
set_target_properties(modules_control_submodules_preprocessor_submodule_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_submodules_preprocessor_submodule_lib
  cyber::cyber
  cyber::time::clock
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::latency_recorder::latency_recorder
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::common::util::util
  modules::common::vehicle_state::vehicle_state_provider
  modules::control::common::control_gflags
  modules::control::common::dependency_injector
  modules::control::proto::control_cmd_cc_proto
  modules::control::proto::control_common_conf_cc_proto
  modules::control::proto::pad_msg_cc_proto
  modules::control::proto::preprocessor_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::planning::proto::planning_cc_proto
)
add_library(modules::control::submodules::preprocessor_submodule_lib  ALIAS   modules_control_submodules_preprocessor_submodule_lib)

add_library(modules_control_submodules_mpc_controller_submodule_lib  SHARED
  mpc_controller_submodule.cc
)
set_target_properties(modules_control_submodules_mpc_controller_submodule_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_submodules_mpc_controller_submodule_lib
  cyber::cyber
  cyber::time::clock
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::latency_recorder::latency_recorder
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::common::util::util
  modules::common::vehicle_state::vehicle_state_provider
  modules::control::common::control_gflags
  modules::control::controller::controller
  modules::control::proto::calibration_table_cc_proto
  modules::control::proto::control_cmd_cc_proto
  modules::control::proto::control_conf_cc_proto
  modules::control::proto::pad_msg_cc_proto
  modules::control::proto::preprocessor_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::planning::proto::planning_cc_proto
  ${gflags_LIBRARIES}
  
)
add_library(modules::control::submodules::mpc_controller_submodule_lib  ALIAS   modules_control_submodules_mpc_controller_submodule_lib)

add_library(modules_control_submodules_lat_lon_controller_submodule_lib  SHARED
  lat_lon_controller_submodule.cc
)
set_target_properties(modules_control_submodules_lat_lon_controller_submodule_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_submodules_lat_lon_controller_submodule_lib
  cyber::cyber
  cyber::time::clock
  modules::common::adapters::adapter_gflags
  modules::common::latency_recorder::latency_recorder
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::common::util::util
  modules::common::vehicle_state::vehicle_state_provider
  modules::control::common::control_gflags
  modules::control::controller::controller
  modules::control::proto::local_view_cc_proto
  modules::control::proto::preprocessor_cc_proto
  ${gflags_LIBRARIES}
  
)
add_library(modules::control::submodules::lat_lon_controller_submodule_lib  ALIAS   modules_control_submodules_lat_lon_controller_submodule_lib)

add_library(modules_control_submodules_postprocessor_submodule_lib  SHARED
  postprocessor_submodule.cc
)
set_target_properties(modules_control_submodules_postprocessor_submodule_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_submodules_postprocessor_submodule_lib
  cyber::cyber
  cyber::time::clock
  modules::common::adapters::adapter_gflags
  modules::common::latency_recorder::latency_recorder
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::common::util::util
  modules::common::vehicle_state::vehicle_state_provider
  modules::control::common::control_gflags
  modules::control::controller::controller
  modules::control::proto::calibration_table_cc_proto
  modules::control::proto::control_cmd_cc_proto
  modules::control::proto::control_common_conf_cc_proto
  modules::control::proto::control_conf_cc_proto
  modules::control::proto::pad_msg_cc_proto
  modules::control::proto::preprocessor_cc_proto
  modules::localization::proto::localization_cc_proto
  ${gflags_LIBRARIES}
  
)
add_library(modules::control::submodules::postprocessor_submodule_lib  ALIAS   modules_control_submodules_postprocessor_submodule_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(control_module  SHARED
  ${virtual_cc}
)
set_target_properties(control_module  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(control_module
  modules::control::submodules::control_module_lib
)
set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(preprocessor_submodule  SHARED
  ${virtual_cc}
)
set_target_properties(preprocessor_submodule  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(preprocessor_submodule
  modules::control::submodules::preprocessor_submodule_lib
)
set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(mpc_controller_submodule  SHARED
  ${virtual_cc}
)
set_target_properties(mpc_controller_submodule  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(mpc_controller_submodule
  modules::control::submodules::mpc_controller_submodule_lib
)
set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(lat_lon_controller_submodule  SHARED
  ${virtual_cc}
)
set_target_properties(lat_lon_controller_submodule  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(lat_lon_controller_submodule
  modules::control::submodules::lat_lon_controller_submodule_lib
)
set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(postprocessor_submodule  SHARED
  ${virtual_cc}
)
set_target_properties(postprocessor_submodule  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(postprocessor_submodule
  modules::control::submodules::postprocessor_submodule_lib
)
