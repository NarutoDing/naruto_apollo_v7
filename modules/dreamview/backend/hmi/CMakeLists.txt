cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_hmi)
message("${Green} [info] modules_dreamview_backend_hmi cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_hmi_vehicle_manager  SHARED
  vehicle_manager.cc
)
set_target_properties(modules_dreamview_backend_hmi_vehicle_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_hmi_vehicle_manager
  cyber::cyber
  modules::common::configs::vehicle_config_helper
  modules::common::util::util
  modules::common::util::string_util
  modules::dreamview::proto::hmi_config_cc_proto
  ${absl}
)
add_library(modules::dreamview::backend::hmi::vehicle_manager  ALIAS   modules_dreamview_backend_hmi_vehicle_manager)

add_library(modules_dreamview_backend_hmi_hmi  SHARED
  hmi.cc
)
set_target_properties(modules_dreamview_backend_hmi_hmi  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_hmi_hmi
  modules::dreamview::backend::hmi::hmi_worker
  cyber::common::file
  modules::common::adapters::adapter_gflags
  modules::common::configs::vehicle_config_helper
  modules::common::monitor_log::monitor_log
  modules::common::util::json_util
  modules::common::util::map_util
  modules::dreamview::backend::fuel_monitor::fuel_monitor_manager
  modules::dreamview::backend::handlers::websocket_handler
  modules::dreamview::backend::map::map_service
  modules::dreamview::backend::point_cloud::point_cloud_updater
)
add_library(modules::dreamview::backend::hmi::hmi  ALIAS   modules_dreamview_backend_hmi_hmi)

add_library(modules_dreamview_backend_hmi_hmi_worker  SHARED
  hmi_worker.cc
)
set_target_properties(modules_dreamview_backend_hmi_hmi_worker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_hmi_hmi_worker
  modules::dreamview::backend::hmi::vehicle_manager
  cyber::cyber
  cyber::proto::dag_conf_cc_proto
  modules::audio::proto::audio_event_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::configs::config_gflags
  modules::common::kv_db::kv_db
  modules::common::proto::drive_event_cc_proto
  modules::common::util::future
  modules::common::util::map_util
  modules::common::util::message_util
  modules::control::proto::pad_msg_cc_proto
  modules::dreamview::backend::common::dreamview_gflags
  modules::dreamview::backend::fuel_monitor::data_collection_monitor
  modules::dreamview::backend::fuel_monitor::fuel_monitor_gflags
  modules::dreamview::backend::fuel_monitor::fuel_monitor_manager
  modules::dreamview::backend::fuel_monitor::preprocess_monitor
  modules::dreamview::proto::hmi_config_cc_proto
  modules::dreamview::proto::hmi_mode_cc_proto
  modules::dreamview::proto::hmi_status_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::monitor::proto::system_status_cc_proto
  ${boost}
  ${absl}
)
add_library(modules::dreamview::backend::hmi::hmi_worker  ALIAS   modules_dreamview_backend_hmi_hmi_worker)

add_executable(vehicle_manager_main
  vehicle_manager_main.cc
)
target_link_libraries(vehicle_manager_main
  modules::dreamview::backend::hmi::vehicle_manager
)
