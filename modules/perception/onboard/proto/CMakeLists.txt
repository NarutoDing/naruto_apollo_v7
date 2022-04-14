cmake_minimum_required(VERSION 3.16)

project(modules_perception_onboard_proto)
message("${Green} [info] modules_perception_onboard_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/perception/onboard/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_perception_onboard_proto_trafficlights_perception_component_cc_proto  SHARED
  trafficlights_perception_component.pb.cc
)
set_target_properties(modules_perception_onboard_proto_trafficlights_perception_component_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::onboard::proto::trafficlights_perception_component_cc_proto  ALIAS   modules_perception_onboard_proto_trafficlights_perception_component_cc_proto)

add_library(modules_perception_onboard_proto_radar_component_config_cc_proto  SHARED
  radar_component_config.pb.cc
)
set_target_properties(modules_perception_onboard_proto_radar_component_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::onboard::proto::radar_component_config_cc_proto  ALIAS   modules_perception_onboard_proto_radar_component_config_cc_proto)

add_library(modules_perception_onboard_proto_fusion_camera_detection_component_cc_proto  SHARED
  fusion_camera_detection_component.pb.cc
)
set_target_properties(modules_perception_onboard_proto_fusion_camera_detection_component_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::onboard::proto::fusion_camera_detection_component_cc_proto  ALIAS   modules_perception_onboard_proto_fusion_camera_detection_component_cc_proto)

add_library(modules_perception_onboard_proto_lane_perception_component_cc_proto  SHARED
  lane_perception_component.pb.cc
)
set_target_properties(modules_perception_onboard_proto_lane_perception_component_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::onboard::proto::lane_perception_component_cc_proto  ALIAS   modules_perception_onboard_proto_lane_perception_component_cc_proto)

add_library(modules_perception_onboard_proto_motion_service_cc_proto  SHARED
  motion_service.pb.cc
)
set_target_properties(modules_perception_onboard_proto_motion_service_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::onboard::proto::motion_service_cc_proto  ALIAS   modules_perception_onboard_proto_motion_service_cc_proto)

add_library(modules_perception_onboard_proto_lidar_component_config_cc_proto  SHARED
  lidar_component_config.pb.cc
)
set_target_properties(modules_perception_onboard_proto_lidar_component_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::onboard::proto::lidar_component_config_cc_proto  ALIAS   modules_perception_onboard_proto_lidar_component_config_cc_proto)

add_library(modules_perception_onboard_proto_fusion_component_config_cc_proto  SHARED
  fusion_component_config.pb.cc
)
set_target_properties(modules_perception_onboard_proto_fusion_component_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::onboard::proto::fusion_component_config_cc_proto  ALIAS   modules_perception_onboard_proto_fusion_component_config_cc_proto)

