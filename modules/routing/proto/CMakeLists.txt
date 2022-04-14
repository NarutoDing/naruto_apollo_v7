cmake_minimum_required(VERSION 3.16)

project(modules_routing_proto)
message("${Green} [info] modules_routing_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/routing/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_routing_proto_poi_cc_proto  SHARED
  poi.pb.cc
)
set_target_properties(modules_routing_proto_poi_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_proto_poi_cc_proto
  modules::routing::proto::routing_cc_proto
)
add_library(modules::routing::proto::poi_cc_proto  ALIAS   modules_routing_proto_poi_cc_proto)

add_library(modules_routing_proto_routing_cc_proto  SHARED
  routing.pb.cc
)
set_target_properties(modules_routing_proto_routing_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_proto_routing_cc_proto
  modules::common::proto::error_code_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::map::proto::map_parking_space_cc_proto
  modules::map::proto::map_geometry_cc_proto
)
add_library(modules::routing::proto::routing_cc_proto  ALIAS   modules_routing_proto_routing_cc_proto)

add_library(modules_routing_proto_routing_config_cc_proto  SHARED
  routing_config.pb.cc
)
set_target_properties(modules_routing_proto_routing_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::routing::proto::routing_config_cc_proto  ALIAS   modules_routing_proto_routing_config_cc_proto)

add_library(modules_routing_proto_topo_graph_cc_proto  SHARED
  topo_graph.pb.cc
)
set_target_properties(modules_routing_proto_topo_graph_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_proto_topo_graph_cc_proto
  modules::map::proto::map_geometry_cc_proto
)
add_library(modules::routing::proto::topo_graph_cc_proto  ALIAS   modules_routing_proto_topo_graph_cc_proto)

