cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_point_cloud)
message("${Green} [info] modules_dreamview_backend_point_cloud cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_point_cloud_point_cloud_updater  SHARED
  point_cloud_updater.cc
)
set_target_properties(modules_dreamview_backend_point_cloud_point_cloud_updater  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_point_cloud_point_cloud_updater
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::math::math
  modules::dreamview::backend::common::dreamview_gflags
  modules::dreamview::backend::handlers::websocket_handler
  modules::dreamview::backend::simulation_world::simulation_world_updater
  modules::dreamview::proto::point_cloud_cc_proto
  modules::drivers::proto::pointcloud_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  modules::localization::proto::localization_cc_proto
  ${boost}
  ${yaml}
  ${json}
  ${Protobuf_LIBRARIES}
  ${pcl}
)
add_library(modules::dreamview::backend::point_cloud::point_cloud_updater  ALIAS   modules_dreamview_backend_point_cloud_point_cloud_updater)

