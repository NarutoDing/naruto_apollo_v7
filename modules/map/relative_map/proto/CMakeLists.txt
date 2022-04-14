cmake_minimum_required(VERSION 3.16)

project(modules_map_relative_map_proto)
message("${Green} [info] modules_map_relative_map_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/map/relative_map/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_map_relative_map_proto_navigation_cc_proto  SHARED
  navigation.pb.cc
)
set_target_properties(modules_map_relative_map_proto_navigation_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_relative_map_proto_navigation_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::map::proto::map_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
)
add_library(modules::map::relative_map::proto::navigation_cc_proto  ALIAS   modules_map_relative_map_proto_navigation_cc_proto)

add_library(modules_map_relative_map_proto_navigator_config_cc_proto  SHARED
  navigator_config.pb.cc
)
set_target_properties(modules_map_relative_map_proto_navigator_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::map::relative_map::proto::navigator_config_cc_proto  ALIAS   modules_map_relative_map_proto_navigator_config_cc_proto)

add_library(modules_map_relative_map_proto_relative_map_config_cc_proto  SHARED
  relative_map_config.pb.cc
)
set_target_properties(modules_map_relative_map_proto_relative_map_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::map::relative_map::proto::relative_map_config_cc_proto  ALIAS   modules_map_relative_map_proto_relative_map_config_cc_proto)

