cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_feature_extractor_tfe)
message("${Green} [info] modules_perception_camera_lib_feature_extractor_tfe cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_feature_extractor_tfe_external_feature_extractor  SHARED
  external_feature_extractor.cc
)
set_target_properties(modules_perception_camera_lib_feature_extractor_tfe_external_feature_extractor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_feature_extractor_tfe_external_feature_extractor
  cyber::common::file
  modules::perception::camera::common::common
  modules::perception::camera::lib::feature_extractor::tfe::proto::tracking_feature_cc_proto
  modules::perception::camera::lib::interface::interface
  modules::perception::inference::inference_factory
  modules::perception::inference::inference_lib
  modules::perception::inference::utils::inference_resize_lib
  modules::perception::inference::utils::inference_util_lib
)
add_library(modules::perception::camera::lib::feature_extractor::tfe::external_feature_extractor  ALIAS   modules_perception_camera_lib_feature_extractor_tfe_external_feature_extractor)

add_library(modules_perception_camera_lib_feature_extractor_tfe_project_feature  SHARED
  project_feature.cc
)
set_target_properties(modules_perception_camera_lib_feature_extractor_tfe_project_feature  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_feature_extractor_tfe_project_feature
  cyber::common::file
  modules::perception::camera::common::common
  modules::perception::camera::lib::feature_extractor::tfe::proto::tracking_feature_cc_proto
  modules::perception::camera::lib::interface::interface
  modules::perception::inference::inference_factory
  modules::perception::inference::utils::inference_gemm_lib
  modules::perception::inference::utils::inference_util_lib
)
add_library(modules::perception::camera::lib::feature_extractor::tfe::project_feature  ALIAS   modules_perception_camera_lib_feature_extractor_tfe_project_feature)

add_library(modules_perception_camera_lib_feature_extractor_tfe_tracking_feat_extractor  SHARED
  tracking_feat_extractor.cc
)
set_target_properties(modules_perception_camera_lib_feature_extractor_tfe_tracking_feat_extractor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_feature_extractor_tfe_tracking_feat_extractor
  cyber::common::file
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::feature_extractor::tfe::proto::tracking_feature_cc_proto
  modules::perception::camera::lib::interface::interface
  modules::perception::inference::inference_factory
  modules::perception::inference::operators::perception_inference_operators
  modules::perception::inference::utils::inference_gemm_lib
  modules::perception::inference::utils::inference_util_lib
  
)
add_library(modules::perception::camera::lib::feature_extractor::tfe::tracking_feat_extractor  ALIAS   modules_perception_camera_lib_feature_extractor_tfe_tracking_feat_extractor)

