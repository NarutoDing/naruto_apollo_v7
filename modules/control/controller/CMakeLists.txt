cmake_minimum_required(VERSION 3.16)

project(modules_control_controller)
message("${Green} [info] modules_control_controller cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_control_controller_controller_interface  SHARED
  ${virtual_cc}
  controller.h
)
set_target_properties(modules_control_controller_controller_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_controller_controller_interface
  modules::control::common::dependency_injector
)
add_library(modules::control::controller::controller_interface  ALIAS   modules_control_controller_controller_interface)

add_library(modules_control_controller_lat_controller  SHARED
  lat_controller.cc
)
set_target_properties(modules_control_controller_lat_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_controller_lat_controller
  modules::control::controller::controller_interface
  cyber::cyber
  cyber::time::clock
  modules::common::configs::config_gflags
  modules::common::configs::vehicle_config_helper
  modules::common::filters::digital_filter
  modules::common::filters::digital_filter_coefficients
  modules::common::filters::mean_filter
  modules::common::math::euler_angles_zxy
  modules::common::math::geometry
  modules::common::math::lqr
  modules::common::math::mpc_osqp
  modules::common::status::status
  modules::control::common::control_gflags
  modules::control::common::interpolation_1d
  modules::control::common::leadlag_controller
  modules::control::common::mrac_controller
  modules::control::common::trajectory_analyzer
  modules::control::proto::calibration_table_cc_proto
  modules::control::proto::control_cmd_cc_proto
  modules::control::proto::control_conf_cc_proto
  modules::control::proto::gain_scheduler_conf_cc_proto
  modules::control::proto::input_debug_cc_proto
  modules::control::proto::lat_controller_conf_cc_proto
  modules::control::proto::lon_controller_conf_cc_proto
  modules::control::proto::mpc_controller_conf_cc_proto
  modules::control::proto::mrac_conf_cc_proto
  modules::control::proto::pad_msg_cc_proto
  ${absl}
  ${eigen}
)
add_library(modules::control::controller::lat_controller  ALIAS   modules_control_controller_lat_controller)

add_library(modules_control_controller_lon_controller  SHARED
  lon_controller.cc
)
set_target_properties(modules_control_controller_lon_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_controller_lon_controller
  modules::control::controller::controller_interface
  cyber::cyber
  modules::common::configs::vehicle_config_helper
  modules::common::filters::digital_filter
  modules::common::filters::digital_filter_coefficients
  modules::common::status::status
  modules::control::common::control_gflags
  modules::control::common::interpolation_2d
  modules::control::common::leadlag_controller
  modules::control::common::pid_controller
  modules::control::common::trajectory_analyzer
  modules::control::proto::calibration_table_cc_proto
  modules::control::proto::control_cmd_cc_proto
  modules::control::proto::control_conf_cc_proto
  modules::control::proto::gain_scheduler_conf_cc_proto
  modules::control::proto::input_debug_cc_proto
  modules::control::proto::lat_controller_conf_cc_proto
  modules::control::proto::lon_controller_conf_cc_proto
  modules::control::proto::mpc_controller_conf_cc_proto
  modules::control::proto::mrac_conf_cc_proto
  modules::control::proto::pad_msg_cc_proto
  modules::localization::common::localization_common
  ${absl}
)
add_library(modules::control::controller::lon_controller  ALIAS   modules_control_controller_lon_controller)

add_library(modules_control_controller_mpc_controller  SHARED
  mpc_controller.cc
)
set_target_properties(modules_control_controller_mpc_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_controller_mpc_controller
  modules::control::controller::controller_interface
  cyber::cyber
  cyber::time::clock
  modules::common::configs::vehicle_config_helper
  modules::common::filters::digital_filter
  modules::common::filters::digital_filter_coefficients
  modules::common::filters::mean_filter
  modules::common::math::euler_angles_zxy
  modules::common::math::geometry
  modules::common::math::lqr
  modules::common::math::mpc_osqp
  modules::common::proto::geometry_cc_proto
  modules::common::status::status
  modules::control::common::control_gflags
  modules::control::common::interpolation_1d
  modules::control::common::interpolation_2d
  modules::control::common::trajectory_analyzer
  modules::control::proto::calibration_table_cc_proto
  modules::control::proto::control_cmd_cc_proto
  modules::control::proto::control_conf_cc_proto
  modules::control::proto::gain_scheduler_conf_cc_proto
  modules::control::proto::input_debug_cc_proto
  modules::control::proto::lat_controller_conf_cc_proto
  modules::control::proto::lon_controller_conf_cc_proto
  modules::control::proto::mpc_controller_conf_cc_proto
  modules::control::proto::mrac_conf_cc_proto
  modules::control::proto::pad_msg_cc_proto
  ${absl}
  ${eigen}
)
add_library(modules::control::controller::mpc_controller  ALIAS   modules_control_controller_mpc_controller)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_control_controller_controller  SHARED
  ${virtual_cc}
)
set_target_properties(modules_control_controller_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_controller_controller
  modules::control::controller::controller_agent
  modules::control::controller::controller_interface
  modules::control::controller::lat_controller
  modules::control::controller::lon_controller
  modules::control::controller::mpc_controller
  ${eigen}
)
add_library(modules::control::controller::controller  ALIAS   modules_control_controller_controller)

add_library(modules_control_controller_controller_agent  SHARED
  controller_agent.cc
)
set_target_properties(modules_control_controller_controller_agent  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_controller_controller_agent
  modules::control::controller::controller_interface
  modules::control::controller::lat_controller
  modules::control::controller::lon_controller
  modules::control::controller::mpc_controller
  cyber::cyber
  cyber::time::clock
  modules::common::util::factory
  modules::control::common::dependency_injector
  modules::control::proto::control_cmd_cc_proto
  modules::planning::proto::planning_cc_proto
  ${osqp}
)
add_library(modules::control::controller::controller_agent  ALIAS   modules_control_controller_controller_agent)

