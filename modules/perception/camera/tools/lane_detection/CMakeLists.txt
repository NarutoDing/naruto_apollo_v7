cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_tools_lane_detection)
message("${Green} [info] modules_perception_camera_tools_lane_detection cmakelist ${ColourReset}")

add_library(modules_perception_camera_tools_lane_detection_lane_common  SHARED
  lane_common.cc
)
set_target_properties(modules_perception_camera_tools_lane_detection_lane_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_tools_lane_detection_lane_common
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::lib::lane::common::common_functions
)
add_library(modules::perception::camera::tools::lane_detection::lane_common  ALIAS   modules_perception_camera_tools_lane_detection_lane_common)

add_executable(lane_denseline_eval
  lane_denseline_eval.cc
)
target_link_libraries(lane_denseline_eval
  modules::perception::camera::tools::lane_detection::lane_common
  cyber::cyber
  modules::common::util::perf_util
  modules::common::util::string_util
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::calibration_service::online_calibration_service::online_calibration_service
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::lane::detector::denseline::denseline_lane_detector
  modules::perception::camera::lib::lane::postprocessor::denseline::denseline_lane_postprocessor
  modules::perception::common::io::io_util
  ${gflags_LIBRARIES}
  ${opencv}
)
