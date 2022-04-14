cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_tools_exporter)
message("${Green} [info] modules_perception_lidar_tools_exporter cmakelist ${ColourReset}")

add_library(modules_perception_lidar_tools_exporter_msgexporterlib  SHARED
  msg_exporter.cc
)
set_target_properties(modules_perception_lidar_tools_exporter_msgexporterlib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_tools_exporter_msgexporterlib
  cyber::cyber
  modules::drivers::proto::pointcloud_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  modules::perception::lidar::common::pcl_util
  modules::perception::onboard::transform_wrapper::transform_wrapper
  ${absl}
  ${opencv}
)
add_library(modules::perception::lidar::tools::exporter::msgexporterlib  ALIAS   modules_perception_lidar_tools_exporter_msgexporterlib)

add_executable(msg_exporter
  msg_exporter_main.cc
)
target_link_libraries(msg_exporter
  modules::perception::lidar::tools::exporter::msgexporterlib
  modules::drivers::proto::pointcloud_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  ${absl}
)
