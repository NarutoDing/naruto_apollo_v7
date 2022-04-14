cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_detector_cnn_segmentation)
message("${Green} [info] modules_perception_lidar_lib_detector_cnn_segmentation cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_cnn_segmentation  SHARED
  cnn_segmentation.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_cnn_segmentation  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_cnn_segmentation
  modules::perception::lidar::lib::detector::cnn_segmentation::disjoint_set
  modules::perception::lidar::lib::detector::cnn_segmentation::feature_generator
  modules::perception::lidar::lib::detector::cnn_segmentation::util
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::perception::base::base
  modules::perception::inference::inference_factory
  modules::perception::inference::inference_lib
  modules::perception::inference::tensorrt::rt_net
  modules::perception::inference::utils::inference_util_lib
  modules::perception::lib::config_manager::config_manager
  modules::perception::lidar::lib::ground_detector::spatio_temporal_ground_detector::spatio_temporal_ground_detector
  modules::perception::lidar::lib::interface::interface
  modules::perception::lidar::lib::roi_filter::hdmap_roi_filter::hdmap_roi_filter
  modules::perception::lidar::lib::detector::cnn_segmentation::proto::cnnseg_config_cc_proto
  modules::perception::lidar::lib::detector::cnn_segmentation::proto::cnnseg_param_cc_proto
  modules::perception::lidar::lib::detector::cnn_segmentation::proto::spp_engine_config_cc_proto
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_engine
  modules::perception::lidar::lib::detector::ncut_segmentation::ncut_segmentation
  modules::perception::lidar::lib::interface::base_lidar_detector
  modules::perception::proto::perception_config_schema_cc_proto
  ${absl}
  
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::cnn_segmentation  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_cnn_segmentation)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_detector_cnn_segmentation_disjoint_set  SHARED
  ${virtual_cc}
  disjoint_set.h
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_disjoint_set  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::cnn_segmentation::disjoint_set  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_disjoint_set)

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_feature_generator  SHARED
  feature_generator.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_feature_generator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_feature_generator
  modules::perception::lidar::lib::detector::cnn_segmentation::util
  modules::perception::base::base
  modules::perception::lidar::lib::detector::cnn_segmentation::proto::cnnseg_param_cc_proto
  
  ${eigen}
  feature_generator_cuda
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::feature_generator  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_feature_generator)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_detector_cnn_segmentation_util  SHARED
  ${virtual_cc}
  util.h
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_util  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::cnn_segmentation::util  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_util)

cuda_add_library(modules_perception_lidar_lib_detector_cnn_segmentation_feature_generator_cuda
  feature_generator.cu
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_feature_generator_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_feature_generator_cuda
  modules::perception::lidar::lib::detector::cnn_segmentation::util
  modules::perception::base::base
  modules::perception::lidar::lib::detector::cnn_segmentation::proto::cnnseg_param_cc_proto
  
  ${eigen}
  ${cuda}
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::feature_generator_cuda  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_feature_generator_cuda)

