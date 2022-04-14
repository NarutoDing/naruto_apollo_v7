cmake_minimum_required(VERSION 3.16)

project(modules_v2x_proto)
message("${Green} [info] modules_v2x_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/v2x/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_v2x_proto_fusion_params_cc_proto  SHARED
  fusion_params.pb.cc
)
set_target_properties(modules_v2x_proto_fusion_params_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::v2x::proto::fusion_params_cc_proto  ALIAS   modules_v2x_proto_fusion_params_cc_proto)

add_library(modules_v2x_proto_v2x_obu_rsi_cc_proto  SHARED
  v2x_obu_rsi.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_obu_rsi_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_proto_v2x_obu_rsi_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::v2x::proto::v2x_obu_rsi_cc_proto  ALIAS   modules_v2x_proto_v2x_obu_rsi_cc_proto)

add_library(modules_v2x_proto_v2x_monitor_cc_proto  SHARED
  v2x_monitor.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_monitor_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::v2x::proto::v2x_monitor_cc_proto  ALIAS   modules_v2x_proto_v2x_monitor_cc_proto)

add_library(modules_v2x_proto_v2x_rsi_cc_proto  SHARED
  v2x_rsi.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_rsi_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_proto_v2x_rsi_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::v2x::proto::v2x_rsi_cc_proto  ALIAS   modules_v2x_proto_v2x_rsi_cc_proto)

add_library(modules_v2x_proto_v2x_service_car_to_obu_cc_proto  SHARED
  v2x_service_car_to_obu.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_service_car_to_obu_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_proto_v2x_service_car_to_obu_cc_proto
  modules::v2x::proto::v2x_car_status_cc_proto
)
add_library(modules::v2x::proto::v2x_service_car_to_obu_cc_proto  ALIAS   modules_v2x_proto_v2x_service_car_to_obu_cc_proto)

add_library(modules_v2x_proto_v2x_junction_cc_proto  SHARED
  v2x_junction.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_junction_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_proto_v2x_junction_cc_proto
  modules::common::proto::geometry_cc_proto
)
add_library(modules::v2x::proto::v2x_junction_cc_proto  ALIAS   modules_v2x_proto_v2x_junction_cc_proto)

add_library(modules_v2x_proto_v2x_obstacles_cc_proto  SHARED
  v2x_obstacles.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_obstacles_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_proto_v2x_obstacles_cc_proto
  modules::common::proto::error_code_cc_proto
  modules::common::proto::header_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
)
add_library(modules::v2x::proto::v2x_obstacles_cc_proto  ALIAS   modules_v2x_proto_v2x_obstacles_cc_proto)

add_library(modules_v2x_proto_v2x_service_obu_to_car_cc_proto  SHARED
  v2x_service_obu_to_car.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_service_obu_to_car_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_proto_v2x_service_obu_to_car_cc_proto
  modules::v2x::proto::v2x_monitor_cc_proto
  modules::v2x::proto::v2x_obstacles_cc_proto
  modules::v2x::proto::v2x_obu_rsi_cc_proto
  modules::v2x::proto::v2x_obu_traffic_light_cc_proto
)
add_library(modules::v2x::proto::v2x_service_obu_to_car_cc_proto  ALIAS   modules_v2x_proto_v2x_service_obu_to_car_cc_proto)

add_library(modules_v2x_proto_v2x_traffic_light_cc_proto  SHARED
  v2x_traffic_light.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_traffic_light_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_proto_v2x_traffic_light_cc_proto
  modules::common::proto::direction_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::v2x::proto::v2x_traffic_light_cc_proto  ALIAS   modules_v2x_proto_v2x_traffic_light_cc_proto)

add_library(modules_v2x_proto_v2x_car_status_cc_proto  SHARED
  v2x_car_status.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_car_status_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_proto_v2x_car_status_cc_proto
  modules::v2x::proto::v2x_junction_cc_proto
  modules::canbus::proto::chassis_detail_cc_proto
  modules::localization::proto::localization_cc_proto
)
add_library(modules::v2x::proto::v2x_car_status_cc_proto  ALIAS   modules_v2x_proto_v2x_car_status_cc_proto)

add_library(modules_v2x_proto_v2x_obu_traffic_light_cc_proto  SHARED
  v2x_obu_traffic_light.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_obu_traffic_light_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_proto_v2x_obu_traffic_light_cc_proto
  modules::v2x::proto::v2x_traffic_light_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::v2x::proto::v2x_obu_traffic_light_cc_proto  ALIAS   modules_v2x_proto_v2x_obu_traffic_light_cc_proto)

add_library(modules_v2x_proto_v2x_traffic_light_policy_cc_proto  SHARED
  v2x_traffic_light_policy.pb.cc
)
set_target_properties(modules_v2x_proto_v2x_traffic_light_policy_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::v2x::proto::v2x_traffic_light_policy_cc_proto  ALIAS   modules_v2x_proto_v2x_traffic_light_policy_cc_proto)

