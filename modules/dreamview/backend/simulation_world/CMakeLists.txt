cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_simulation_world)
message("${Green} [info] modules_dreamview_backend_simulation_world cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_simulation_world_simulation_world_service  SHARED
  simulation_world_service.cc
)
set_target_properties(modules_dreamview_backend_simulation_world_simulation_world_service  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_simulation_world_simulation_world_service
  cyber::cyber
  modules::audio::proto::audio_cc_proto
  modules::audio::proto::audio_event_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::configs::vehicle_config_helper
  modules::common::math::quaternion
  modules::common::monitor_log::monitor_log
  modules::common::proto::drive_event_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::util::util
  modules::common::util::map_util
  modules::common::util::points_downsampler
  modules::control::proto::control_cmd_cc_proto
  modules::dreamview::backend::common::dreamview_gflags
  modules::dreamview::backend::map::map_service
  modules::dreamview::proto::simulation_world_cc_proto
  modules::localization::proto::gps_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::map::hdmap::hdmap_util
  modules::perception::proto::perception_obstacle_cc_proto
  modules::planning::proto::planning_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
  modules::storytelling::proto::story_cc_proto
  modules::task_manager::proto::task_manager_cc_proto
  ${json}
  ${absl}
)
add_library(modules::dreamview::backend::simulation_world::simulation_world_service  ALIAS   modules_dreamview_backend_simulation_world_simulation_world_service)

add_library(modules_dreamview_backend_simulation_world_simulation_world_updater  SHARED
  simulation_world_updater.cc
)
set_target_properties(modules_dreamview_backend_simulation_world_simulation_world_updater  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_simulation_world_simulation_world_updater
  modules::dreamview::backend::simulation_world::simulation_world_service
  modules::common::util::map_util
  modules::dreamview::backend::common::dreamview_gflags
  modules::dreamview::backend::fuel_monitor::fuel_monitor_manager
  modules::dreamview::backend::handlers::websocket_handler
  modules::dreamview::backend::map::map_service
  modules::dreamview::backend::perception_camera_updater::perception_camera_updater
  modules::dreamview::backend::sim_control::sim_control
  modules::routing::proto::poi_cc_proto
  modules::task_manager::proto::task_manager_cc_proto
  ${boost}
)
add_library(modules::dreamview::backend::simulation_world::simulation_world_updater  ALIAS   modules_dreamview_backend_simulation_world_simulation_world_updater)

