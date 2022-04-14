cmake_minimum_required(VERSION 3.16)

project(modules_monitor_software)
message("${Green} [info] modules_monitor_software cmakelist ${ColourReset}")

add_library(modules_monitor_software_process_monitor  SHARED
  process_monitor.cc
)
set_target_properties(modules_monitor_software_process_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_software_process_monitor
  modules::monitor::software::summary_monitor
  modules::dreamview::proto::hmi_mode_cc_proto
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
  ${gflags_LIBRARIES}
)
add_library(modules::monitor::software::process_monitor  ALIAS   modules_monitor_software_process_monitor)

add_library(modules_monitor_software_module_monitor  SHARED
  module_monitor.cc
)
set_target_properties(modules_monitor_software_module_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_software_module_monitor
  modules::monitor::software::summary_monitor
  cyber::service_discovery::node_manager
  modules::dreamview::proto::hmi_mode_cc_proto
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
  ${absl}
)
add_library(modules::monitor::software::module_monitor  ALIAS   modules_monitor_software_module_monitor)

add_library(modules_monitor_software_camera_monitor  SHARED
  camera_monitor.cc
)
set_target_properties(modules_monitor_software_camera_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_software_camera_monitor
  modules::monitor::software::summary_monitor
  cyber::common::log
  modules::dreamview::proto::hmi_mode_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
  ${absl}
)
add_library(modules::monitor::software::camera_monitor  ALIAS   modules_monitor_software_camera_monitor)

add_library(modules_monitor_software_channel_monitor  SHARED
  channel_monitor.cc
)
set_target_properties(modules_monitor_software_channel_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_software_channel_monitor
  modules::monitor::software::latency_monitor
  modules::monitor::software::summary_monitor
  modules::common::latency_recorder::proto::latency_record_cc_proto
  modules::canbus::proto::chassis_detail_cc_proto
  modules::control::proto::control_cmd_cc_proto
  modules::dreamview::proto::hmi_mode_cc_proto
  modules::drivers::proto::conti_radar_cc_proto
  modules::drivers::proto::pointcloud_cc_proto
  modules::localization::proto::pose_cc_proto
  modules::map::relative_map::proto::navigation_cc_proto
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
  modules::perception::proto::perception_obstacle_cc_proto
  modules::planning::proto::planning_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
  ${absl}
)
add_library(modules::monitor::software::channel_monitor  ALIAS   modules_monitor_software_channel_monitor)

add_library(modules_monitor_software_localization_monitor  SHARED
  localization_monitor.cc
)
set_target_properties(modules_monitor_software_localization_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_software_localization_monitor
  modules::monitor::software::summary_monitor
  modules::common::adapters::adapter_gflags
  modules::localization::proto::localization_cc_proto
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
)
add_library(modules::monitor::software::localization_monitor  ALIAS   modules_monitor_software_localization_monitor)

add_library(modules_monitor_software_functional_safety_monitor  SHARED
  functional_safety_monitor.cc
)
set_target_properties(modules_monitor_software_functional_safety_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_software_functional_safety_monitor
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
)
add_library(modules::monitor::software::functional_safety_monitor  ALIAS   modules_monitor_software_functional_safety_monitor)

add_library(modules_monitor_software_summary_monitor  SHARED
  summary_monitor.cc
)
set_target_properties(modules_monitor_software_summary_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_software_summary_monitor
  modules::common::adapters::adapter_gflags
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
  ${absl}
)
add_library(modules::monitor::software::summary_monitor  ALIAS   modules_monitor_software_summary_monitor)

add_library(modules_monitor_software_recorder_monitor  SHARED
  recorder_monitor.cc
)
set_target_properties(modules_monitor_software_recorder_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_software_recorder_monitor
  modules::monitor::software::summary_monitor
  modules::common::adapters::adapter_gflags
  modules::data::tools::smart_recorder::proto::smart_recorder_status_cc_proto
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
)
add_library(modules::monitor::software::recorder_monitor  ALIAS   modules_monitor_software_recorder_monitor)

add_library(modules_monitor_software_latency_monitor  SHARED
  latency_monitor.cc
)
set_target_properties(modules_monitor_software_latency_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_monitor_software_latency_monitor
  modules::monitor::software::summary_monitor
  modules::common::adapters::adapter_gflags
  modules::common::latency_recorder::proto::latency_record_cc_proto
  modules::monitor::common::monitor_manager
  modules::monitor::common::recurrent_runner
)
add_library(modules::monitor::software::latency_monitor  ALIAS   modules_monitor_software_latency_monitor)

