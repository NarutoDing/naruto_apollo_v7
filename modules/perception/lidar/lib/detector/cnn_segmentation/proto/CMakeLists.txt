cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_detector_cnn_segmentation_proto)
message("${Green} [info] modules_perception_lidar_lib_detector_cnn_segmentation_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/perception/lidar/lib/detector/cnn_segmentation/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_proto_spp_engine_config_cc_proto  SHARED
  spp_engine_config.pb.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_proto_spp_engine_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::cnn_segmentation::proto::spp_engine_config_cc_proto  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_proto_spp_engine_config_cc_proto)

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_proto_cnnseg_param_cc_proto  SHARED
  cnnseg_param.pb.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_proto_cnnseg_param_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::cnn_segmentation::proto::cnnseg_param_cc_proto  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_proto_cnnseg_param_cc_proto)

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_proto_cnnseg_config_cc_proto  SHARED
  cnnseg_config.pb.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_proto_cnnseg_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::cnn_segmentation::proto::cnnseg_config_cc_proto  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_proto_cnnseg_config_cc_proto)

