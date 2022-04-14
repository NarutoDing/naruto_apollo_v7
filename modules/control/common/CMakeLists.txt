cmake_minimum_required(VERSION 3.16)

project(modules_control_common)
message("${Green} [info] modules_control_common cmakelist ${ColourReset}")

add_library(modules_control_common_control_gflags  SHARED
  control_gflags.cc
)
set_target_properties(modules_control_common_control_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_control_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::control::common::control_gflags  ALIAS   modules_control_common_control_gflags)

add_library(modules_control_common_hysteresis_filter  SHARED
  hysteresis_filter.cc
)
set_target_properties(modules_control_common_hysteresis_filter  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::control::common::hysteresis_filter  ALIAS   modules_control_common_hysteresis_filter)

add_library(modules_control_common_interpolation_1d  SHARED
  interpolation_1d.cc
)
set_target_properties(modules_control_common_interpolation_1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_interpolation_1d
  cyber::cyber
  ${eigen}
)
add_library(modules::control::common::interpolation_1d  ALIAS   modules_control_common_interpolation_1d)

add_library(modules_control_common_interpolation_2d  SHARED
  interpolation_2d.cc
)
set_target_properties(modules_control_common_interpolation_2d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_interpolation_2d
  cyber::cyber
  ${eigen}
)
add_library(modules::control::common::interpolation_2d  ALIAS   modules_control_common_interpolation_2d)

add_library(modules_control_common_leadlag_controller  SHARED
  leadlag_controller.cc
)
set_target_properties(modules_control_common_leadlag_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_leadlag_controller
  cyber::common::log
  modules::control::proto::leadlag_conf_cc_proto
)
add_library(modules::control::common::leadlag_controller  ALIAS   modules_control_common_leadlag_controller)

add_library(modules_control_common_mrac_controller  SHARED
  mrac_controller.cc
)
set_target_properties(modules_control_common_mrac_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_mrac_controller
  cyber::cyber
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::math::matrix_operations
  modules::common::status::status
  modules::common::util::util
  modules::control::proto::mrac_conf_cc_proto
  ${absl}
  ${eigen}
)
add_library(modules::control::common::mrac_controller  ALIAS   modules_control_common_mrac_controller)

add_library(modules_control_common_pid_controller  SHARED
  pid_controller.cc
)
set_target_properties(modules_control_common_pid_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_pid_controller
  cyber::common::log
  modules::control::proto::pid_conf_cc_proto
)
add_library(modules::control::common::pid_controller  ALIAS   modules_control_common_pid_controller)

add_library(modules_control_common_pid_BC_controller  SHARED
  pid_BC_controller.cc
)
set_target_properties(modules_control_common_pid_BC_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_pid_BC_controller
  modules::control::common::pid_controller
  cyber::cyber
  modules::common::math::math
)
add_library(modules::control::common::pid_BC_controller  ALIAS   modules_control_common_pid_BC_controller)

add_library(modules_control_common_pid_IC_controller  SHARED
  pid_IC_controller.cc
)
set_target_properties(modules_control_common_pid_IC_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_pid_IC_controller
  modules::control::common::pid_controller
  cyber::cyber
  modules::common::math::math
)
add_library(modules::control::common::pid_IC_controller  ALIAS   modules_control_common_pid_IC_controller)

add_library(modules_control_common_trajectory_analyzer  SHARED
  trajectory_analyzer.cc
)
set_target_properties(modules_control_common_trajectory_analyzer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_trajectory_analyzer
  modules::control::common::control_gflags
  cyber::common::log
  modules::common::math::linear_interpolation
  modules::common::math::search
  modules::common::proto::pnc_point_cc_proto
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::proto::planning_cc_proto
)
add_library(modules::control::common::trajectory_analyzer  ALIAS   modules_control_common_trajectory_analyzer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_control_common_common  SHARED
  ${virtual_cc}
)
set_target_properties(modules_control_common_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_common
  modules::control::common::control_gflags
  modules::control::common::hysteresis_filter
  modules::control::common::interpolation_1d
  modules::control::common::interpolation_2d
  modules::control::common::leadlag_controller
  modules::control::common::pid_controller
  modules::control::common::trajectory_analyzer
)
add_library(modules::control::common::common  ALIAS   modules_control_common_common)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_control_common_dependency_injector  SHARED
  ${virtual_cc}
  dependency_injector.h
)
set_target_properties(modules_control_common_dependency_injector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_common_dependency_injector
  modules::common::vehicle_state::vehicle_state_provider
)
add_library(modules::control::common::dependency_injector  ALIAS   modules_control_common_dependency_injector)

