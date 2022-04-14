cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_perception_camera_updater)
message("${Green} [info] modules_dreamview_backend_perception_camera_updater cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_perception_camera_updater_perception_camera_updater  SHARED
  perception_camera_updater.cc
)
set_target_properties(modules_dreamview_backend_perception_camera_updater_perception_camera_updater  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_perception_camera_updater_perception_camera_updater
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::proto::geometry_cc_proto
  modules::dreamview::backend::handlers::websocket_handler
  modules::dreamview::proto::camera_update_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::transform::buffer
  modules::transform::proto::transform_cc_proto
  ${eigen}
  ${opencv}
)
add_library(modules::dreamview::backend::perception_camera_updater::perception_camera_updater  ALIAS   modules_dreamview_backend_perception_camera_updater_perception_camera_updater)

