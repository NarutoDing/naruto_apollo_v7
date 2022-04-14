cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_detector_ncut_segmentation_proto)
message("${Green} [info] modules_perception_lidar_lib_detector_ncut_segmentation_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/perception/lidar/lib/detector/ncut_segmentation/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_perception_lidar_lib_detector_ncut_segmentation_proto_ncut_param_cc_proto  SHARED
  ncut_param.pb.cc
)
set_target_properties(modules_perception_lidar_lib_detector_ncut_segmentation_proto_ncut_param_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::ncut_segmentation::proto::ncut_param_cc_proto  ALIAS   modules_perception_lidar_lib_detector_ncut_segmentation_proto_ncut_param_cc_proto)

add_library(modules_perception_lidar_lib_detector_ncut_segmentation_proto_ncut_config_cc_proto  SHARED
  ncut_config.pb.cc
)
set_target_properties(modules_perception_lidar_lib_detector_ncut_segmentation_proto_ncut_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::lidar::lib::detector::ncut_segmentation::proto::ncut_config_cc_proto  ALIAS   modules_perception_lidar_lib_detector_ncut_segmentation_proto_ncut_config_cc_proto)

