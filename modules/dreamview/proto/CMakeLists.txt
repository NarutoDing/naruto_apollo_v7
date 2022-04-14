cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_proto)
message("${Green} [info] modules_dreamview_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/dreamview/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_dreamview_proto_data_collection_table_cc_proto  SHARED
  data_collection_table.pb.cc
)
set_target_properties(modules_dreamview_proto_data_collection_table_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::dreamview::proto::data_collection_table_cc_proto  ALIAS   modules_dreamview_proto_data_collection_table_cc_proto)

add_library(modules_dreamview_proto_chart_cc_proto  SHARED
  chart.pb.cc
)
set_target_properties(modules_dreamview_proto_chart_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_proto_chart_cc_proto
  modules::common::proto::geometry_cc_proto
)
add_library(modules::dreamview::proto::chart_cc_proto  ALIAS   modules_dreamview_proto_chart_cc_proto)

add_library(modules_dreamview_proto_simulation_world_cc_proto  SHARED
  simulation_world.pb.cc
)
set_target_properties(modules_dreamview_proto_simulation_world_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_proto_simulation_world_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::monitor_log::proto::monitor_log_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
  modules::planning::proto::planning_internal_cc_proto
  modules::prediction::proto::feature_cc_proto
  modules::routing::proto::routing_cc_proto
)
add_library(modules::dreamview::proto::simulation_world_cc_proto  ALIAS   modules_dreamview_proto_simulation_world_cc_proto)

add_library(modules_dreamview_proto_hmi_status_cc_proto  SHARED
  hmi_status.pb.cc
)
set_target_properties(modules_dreamview_proto_hmi_status_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_proto_hmi_status_cc_proto
  modules::common::proto::header_cc_proto
  modules::monitor::proto::system_status_cc_proto
)
add_library(modules::dreamview::proto::hmi_status_cc_proto  ALIAS   modules_dreamview_proto_hmi_status_cc_proto)

add_library(modules_dreamview_proto_hmi_mode_cc_proto  SHARED
  hmi_mode.pb.cc
)
set_target_properties(modules_dreamview_proto_hmi_mode_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::dreamview::proto::hmi_mode_cc_proto  ALIAS   modules_dreamview_proto_hmi_mode_cc_proto)

add_library(modules_dreamview_proto_camera_update_cc_proto  SHARED
  camera_update.pb.cc
)
set_target_properties(modules_dreamview_proto_camera_update_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::dreamview::proto::camera_update_cc_proto  ALIAS   modules_dreamview_proto_camera_update_cc_proto)

add_library(modules_dreamview_proto_hmi_config_cc_proto  SHARED
  hmi_config.pb.cc
)
set_target_properties(modules_dreamview_proto_hmi_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::dreamview::proto::hmi_config_cc_proto  ALIAS   modules_dreamview_proto_hmi_config_cc_proto)

add_library(modules_dreamview_proto_point_cloud_cc_proto  SHARED
  point_cloud.pb.cc
)
set_target_properties(modules_dreamview_proto_point_cloud_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::dreamview::proto::point_cloud_cc_proto  ALIAS   modules_dreamview_proto_point_cloud_cc_proto)

add_library(modules_dreamview_proto_preprocess_table_cc_proto  SHARED
  preprocess_table.pb.cc
)
set_target_properties(modules_dreamview_proto_preprocess_table_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::dreamview::proto::preprocess_table_cc_proto  ALIAS   modules_dreamview_proto_preprocess_table_cc_proto)

