cmake_minimum_required(VERSION 3.16)

project(modules_perception_proto)
message("${Green} [info] modules_perception_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/perception/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_perception_proto_roi_boundary_filter_config_cc_proto  SHARED
  roi_boundary_filter_config.pb.cc
)
set_target_properties(modules_perception_proto_roi_boundary_filter_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::roi_boundary_filter_config_cc_proto  ALIAS   modules_perception_proto_roi_boundary_filter_config_cc_proto)

add_library(modules_perception_proto_traffic_light_detection_cc_proto  SHARED
  traffic_light_detection.pb.cc
)
set_target_properties(modules_perception_proto_traffic_light_detection_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_proto_traffic_light_detection_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::perception::proto::traffic_light_detection_cc_proto  ALIAS   modules_perception_proto_traffic_light_detection_cc_proto)

add_library(modules_perception_proto_map_manager_config_cc_proto  SHARED
  map_manager_config.pb.cc
)
set_target_properties(modules_perception_proto_map_manager_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::map_manager_config_cc_proto  ALIAS   modules_perception_proto_map_manager_config_cc_proto)

add_library(modules_perception_proto_fused_classifier_config_cc_proto  SHARED
  fused_classifier_config.pb.cc
)
set_target_properties(modules_perception_proto_fused_classifier_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::fused_classifier_config_cc_proto  ALIAS   modules_perception_proto_fused_classifier_config_cc_proto)

add_library(modules_perception_proto_perception_camera_cc_proto  SHARED
  perception_camera.pb.cc
)
set_target_properties(modules_perception_proto_perception_camera_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_proto_perception_camera_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::perception::proto::perception_camera_cc_proto  ALIAS   modules_perception_proto_perception_camera_cc_proto)

add_library(modules_perception_proto_perception_ultrasonic_cc_proto  SHARED
  perception_ultrasonic.pb.cc
)
set_target_properties(modules_perception_proto_perception_ultrasonic_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_proto_perception_ultrasonic_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::perception::proto::perception_ultrasonic_cc_proto  ALIAS   modules_perception_proto_perception_ultrasonic_cc_proto)

add_library(modules_perception_proto_dst_type_fusion_config_cc_proto  SHARED
  dst_type_fusion_config.pb.cc
)
set_target_properties(modules_perception_proto_dst_type_fusion_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::dst_type_fusion_config_cc_proto  ALIAS   modules_perception_proto_dst_type_fusion_config_cc_proto)

add_library(modules_perception_proto_tracker_config_cc_proto  SHARED
  tracker_config.pb.cc
)
set_target_properties(modules_perception_proto_tracker_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::tracker_config_cc_proto  ALIAS   modules_perception_proto_tracker_config_cc_proto)

add_library(modules_perception_proto_perception_config_schema_cc_proto  SHARED
  perception_config_schema.pb.cc
)
set_target_properties(modules_perception_proto_perception_config_schema_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::perception_config_schema_cc_proto  ALIAS   modules_perception_proto_perception_config_schema_cc_proto)

add_library(modules_perception_proto_dst_existence_fusion_config_cc_proto  SHARED
  dst_existence_fusion_config.pb.cc
)
set_target_properties(modules_perception_proto_dst_existence_fusion_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::dst_existence_fusion_config_cc_proto  ALIAS   modules_perception_proto_dst_existence_fusion_config_cc_proto)

add_library(modules_perception_proto_perception_lane_cc_proto  SHARED
  perception_lane.pb.cc
)
set_target_properties(modules_perception_proto_perception_lane_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_proto_perception_lane_cc_proto
  modules::perception::proto::perception_camera_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::perception::proto::perception_lane_cc_proto  ALIAS   modules_perception_proto_perception_lane_cc_proto)

add_library(modules_perception_proto_motion_service_cc_proto  SHARED
  motion_service.pb.cc
)
set_target_properties(modules_perception_proto_motion_service_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_proto_motion_service_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::perception::proto::motion_service_cc_proto  ALIAS   modules_perception_proto_motion_service_cc_proto)

add_library(modules_perception_proto_pbf_tracker_config_cc_proto  SHARED
  pbf_tracker_config.pb.cc
)
set_target_properties(modules_perception_proto_pbf_tracker_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::pbf_tracker_config_cc_proto  ALIAS   modules_perception_proto_pbf_tracker_config_cc_proto)

add_library(modules_perception_proto_rt_cc_proto  SHARED
  rt.pb.cc
)
set_target_properties(modules_perception_proto_rt_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::rt_cc_proto  ALIAS   modules_perception_proto_rt_cc_proto)

add_library(modules_perception_proto_probabilistic_fusion_config_cc_proto  SHARED
  probabilistic_fusion_config.pb.cc
)
set_target_properties(modules_perception_proto_probabilistic_fusion_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::probabilistic_fusion_config_cc_proto  ALIAS   modules_perception_proto_probabilistic_fusion_config_cc_proto)

add_library(modules_perception_proto_perception_obstacle_cc_proto  SHARED
  perception_obstacle.pb.cc
)
set_target_properties(modules_perception_proto_perception_obstacle_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_proto_perception_obstacle_cc_proto
  modules::common::proto::error_code_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::map::proto::map_lane_cc_proto
)
add_library(modules::perception::proto::perception_obstacle_cc_proto  ALIAS   modules_perception_proto_perception_obstacle_cc_proto)

add_library(modules_perception_proto_ccrf_type_fusion_config_cc_proto  SHARED
  ccrf_type_fusion_config.pb.cc
)
set_target_properties(modules_perception_proto_ccrf_type_fusion_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::ccrf_type_fusion_config_cc_proto  ALIAS   modules_perception_proto_ccrf_type_fusion_config_cc_proto)

add_library(modules_perception_proto_sensor_meta_schema_cc_proto  SHARED
  sensor_meta_schema.pb.cc
)
set_target_properties(modules_perception_proto_sensor_meta_schema_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::proto::sensor_meta_schema_cc_proto  ALIAS   modules_perception_proto_sensor_meta_schema_cc_proto)

