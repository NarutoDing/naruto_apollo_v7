cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_obstacle_detector_smoke)
message("${Green} [info] modules_perception_camera_lib_obstacle_detector_smoke cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_obstacle_detector_smoke_smoke_region_output  SHARED
  region_output.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_detector_smoke_smoke_region_output  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_detector_smoke_smoke_region_output
  modules::perception::camera::lib::obstacle::detector::smoke::smoke_object_maintainer
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::obstacle::detector::smoke::proto::smoke_cc_proto
  ${cuda}
  smoke_region_output_cuda
)
add_library(modules::perception::camera::lib::obstacle::detector::smoke::smoke_region_output  ALIAS   modules_perception_camera_lib_obstacle_detector_smoke_smoke_region_output)

add_library(modules_perception_camera_lib_obstacle_detector_smoke_smoke_obstacle_detector  SHARED
  smoke_obstacle_detector.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_detector_smoke_smoke_obstacle_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_detector_smoke_smoke_obstacle_detector
  modules::perception::camera::lib::obstacle::detector::smoke::smoke_region_output
  modules::perception::camera::lib::obstacle::detector::yolo::region_output
  cyber::common::file
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::feature_extractor::tfe::external_feature_extractor
  modules::perception::camera::lib::feature_extractor::tfe::project_feature
  modules::perception::camera::lib::feature_extractor::tfe::tracking_feat_extractor
  modules::perception::camera::lib::interface::interface
  modules::perception::inference::inference_factory
  modules::perception::inference::inference_lib
  modules::perception::inference::utils::inference_resize_lib
  modules::perception::inference::utils::inference_util_lib
)
add_library(modules::perception::camera::lib::obstacle::detector::smoke::smoke_obstacle_detector  ALIAS   modules_perception_camera_lib_obstacle_detector_smoke_smoke_obstacle_detector)

add_library(modules_perception_camera_lib_obstacle_detector_smoke_smoke_object_maintainer  SHARED
  object_maintainer.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_detector_smoke_smoke_object_maintainer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_detector_smoke_smoke_object_maintainer
  cyber::common::file
  modules::perception::base::base
)
add_library(modules::perception::camera::lib::obstacle::detector::smoke::smoke_object_maintainer  ALIAS   modules_perception_camera_lib_obstacle_detector_smoke_smoke_object_maintainer)

cuda_add_library(modules_perception_camera_lib_obstacle_detector_smoke_smoke_region_output_cuda
  region_output.cu
)
set_target_properties(modules_perception_camera_lib_obstacle_detector_smoke_smoke_region_output_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_detector_smoke_smoke_region_output_cuda
  modules::perception::camera::lib::obstacle::detector::smoke::smoke_object_maintainer
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::obstacle::detector::smoke::proto::smoke_cc_proto
  ${cuda}
)
add_library(modules::perception::camera::lib::obstacle::detector::smoke::smoke_region_output_cuda  ALIAS   modules_perception_camera_lib_obstacle_detector_smoke_smoke_region_output_cuda)

