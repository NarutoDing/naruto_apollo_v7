cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_tools_offline)
message("${Green} [info] modules_perception_camera_tools_offline cmakelist ${ColourReset}")

add_library(modules_perception_camera_tools_offline_visualizer  SHARED
  visualizer.cc
)
set_target_properties(modules_perception_camera_tools_offline_visualizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_tools_offline_visualizer
  modules::perception::camera::tools::offline::transform_server
  modules::common::util::eigen_defs
  modules::perception::camera::app::cipv_camera
  modules::perception::camera::common::common
  modules::perception::proto::motion_service_cc_proto
  ${opencv}
)
add_library(modules::perception::camera::tools::offline::visualizer  ALIAS   modules_perception_camera_tools_offline_visualizer)

add_library(modules_perception_camera_tools_offline_transform_server  SHARED
  transform_server.cc
)
set_target_properties(modules_perception_camera_tools_offline_transform_server  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_tools_offline_transform_server
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::common::common
  ${yaml}
  ${eigen}
)
add_library(modules::perception::camera::tools::offline::transform_server  ALIAS   modules_perception_camera_tools_offline_transform_server)

add_executable(offline_obstacle_pipeline
  offline_obstacle_pipeline.cc
)
target_link_libraries(offline_obstacle_pipeline
  modules::perception::camera::tools::offline::transform_server
  modules::perception::camera::tools::offline::visualizer
  modules::perception::base::base
  modules::perception::camera::app::obstacle_camera_perception
  modules::perception::camera::app::proto::perception_cc_proto
  modules::perception::camera::common::common
  modules::perception::camera::lib::feature_extractor::tfe::proto::tracking_feature_cc_proto
  modules::perception::camera::lib::lane::detector::darkSCNN::darkSCNN_lane_detector
  modules::perception::camera::lib::lane::postprocessor::darkSCNN::darkSCNN_lane_postprocessor
  modules::perception::camera::lib::lane::detector::denseline::denseline_lane_detector
  modules::perception::camera::lib::lane::postprocessor::denseline::denseline_lane_postprocessor
  ${boost}
  ${absl}
  ${opencv}
)
