cmake_minimum_required(VERSION 3.16)

project(modules_third_party_perception_proto)
message("${Green} [info] modules_third_party_perception_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/third_party_perception/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_third_party_perception_proto_radar_obstacle_cc_proto  SHARED
  radar_obstacle.pb.cc
)
set_target_properties(modules_third_party_perception_proto_radar_obstacle_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_proto_radar_obstacle_cc_proto
  modules::common::proto::error_code_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
)
add_library(modules::third_party_perception::proto::radar_obstacle_cc_proto  ALIAS   modules_third_party_perception_proto_radar_obstacle_cc_proto)

add_library(modules_third_party_perception_proto_third_party_perception_component_cc_proto  SHARED
  third_party_perception_component.pb.cc
)
set_target_properties(modules_third_party_perception_proto_third_party_perception_component_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::third_party_perception::proto::third_party_perception_component_cc_proto  ALIAS   modules_third_party_perception_proto_third_party_perception_component_cc_proto)

