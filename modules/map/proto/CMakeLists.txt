cmake_minimum_required(VERSION 3.16)

project(modules_map_proto)
message("${Green} [info] modules_map_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/map/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_map_proto_map_stop_sign_cc_proto  SHARED
  map_stop_sign.pb.cc
)
set_target_properties(modules_map_proto_map_stop_sign_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_stop_sign_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_stop_sign_cc_proto  ALIAS   modules_map_proto_map_stop_sign_cc_proto)

add_library(modules_map_proto_map_junction_cc_proto  SHARED
  map_junction.pb.cc
)
set_target_properties(modules_map_proto_map_junction_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_junction_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_junction_cc_proto  ALIAS   modules_map_proto_map_junction_cc_proto)

add_library(modules_map_proto_map_id_cc_proto  SHARED
  map_id.pb.cc
)
set_target_properties(modules_map_proto_map_id_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::map::proto::map_id_cc_proto  ALIAS   modules_map_proto_map_id_cc_proto)

add_library(modules_map_proto_map_pnc_junction_cc_proto  SHARED
  map_pnc_junction.pb.cc
)
set_target_properties(modules_map_proto_map_pnc_junction_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_pnc_junction_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_pnc_junction_cc_proto  ALIAS   modules_map_proto_map_pnc_junction_cc_proto)

add_library(modules_map_proto_map_road_cc_proto  SHARED
  map_road.pb.cc
)
set_target_properties(modules_map_proto_map_road_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_road_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_road_cc_proto  ALIAS   modules_map_proto_map_road_cc_proto)

add_library(modules_map_proto_map_parking_space_cc_proto  SHARED
  map_parking_space.pb.cc
)
set_target_properties(modules_map_proto_map_parking_space_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_parking_space_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_parking_space_cc_proto  ALIAS   modules_map_proto_map_parking_space_cc_proto)

add_library(modules_map_proto_map_speed_bump_cc_proto  SHARED
  map_speed_bump.pb.cc
)
set_target_properties(modules_map_proto_map_speed_bump_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_speed_bump_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_speed_bump_cc_proto  ALIAS   modules_map_proto_map_speed_bump_cc_proto)

add_library(modules_map_proto_map_signal_cc_proto  SHARED
  map_signal.pb.cc
)
set_target_properties(modules_map_proto_map_signal_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_signal_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
  modules::common::proto::geometry_cc_proto
)
add_library(modules::map::proto::map_signal_cc_proto  ALIAS   modules_map_proto_map_signal_cc_proto)

add_library(modules_map_proto_map_yield_sign_cc_proto  SHARED
  map_yield_sign.pb.cc
)
set_target_properties(modules_map_proto_map_yield_sign_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_yield_sign_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_yield_sign_cc_proto  ALIAS   modules_map_proto_map_yield_sign_cc_proto)

add_library(modules_map_proto_map_clear_area_cc_proto  SHARED
  map_clear_area.pb.cc
)
set_target_properties(modules_map_proto_map_clear_area_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_clear_area_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_clear_area_cc_proto  ALIAS   modules_map_proto_map_clear_area_cc_proto)

add_library(modules_map_proto_map_crosswalk_cc_proto  SHARED
  map_crosswalk.pb.cc
)
set_target_properties(modules_map_proto_map_crosswalk_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_crosswalk_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_crosswalk_cc_proto  ALIAS   modules_map_proto_map_crosswalk_cc_proto)

add_library(modules_map_proto_map_overlap_cc_proto  SHARED
  map_overlap.pb.cc
)
set_target_properties(modules_map_proto_map_overlap_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_overlap_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_overlap_cc_proto  ALIAS   modules_map_proto_map_overlap_cc_proto)

add_library(modules_map_proto_map_lane_cc_proto  SHARED
  map_lane.pb.cc
)
set_target_properties(modules_map_proto_map_lane_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_lane_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_lane_cc_proto  ALIAS   modules_map_proto_map_lane_cc_proto)

add_library(modules_map_proto_map_geometry_cc_proto  SHARED
  map_geometry.pb.cc
)
set_target_properties(modules_map_proto_map_geometry_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_geometry_cc_proto
  modules::common::proto::geometry_cc_proto
)
add_library(modules::map::proto::map_geometry_cc_proto  ALIAS   modules_map_proto_map_geometry_cc_proto)

add_library(modules_map_proto_map_speed_control_cc_proto  SHARED
  map_speed_control.pb.cc
)
set_target_properties(modules_map_proto_map_speed_control_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_speed_control_cc_proto
  modules::map::proto::map_geometry_cc_proto
)
add_library(modules::map::proto::map_speed_control_cc_proto  ALIAS   modules_map_proto_map_speed_control_cc_proto)

add_library(modules_map_proto_map_rsu_cc_proto  SHARED
  map_rsu.pb.cc
)
set_target_properties(modules_map_proto_map_rsu_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_rsu_cc_proto
  modules::map::proto::map_geometry_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::map::proto::map_rsu_cc_proto  ALIAS   modules_map_proto_map_rsu_cc_proto)

add_library(modules_map_proto_map_cc_proto  SHARED
  map.pb.cc
)
set_target_properties(modules_map_proto_map_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_proto_map_cc_proto
  modules::map::proto::map_clear_area_cc_proto
  modules::map::proto::map_crosswalk_cc_proto
  modules::map::proto::map_junction_cc_proto
  modules::map::proto::map_lane_cc_proto
  modules::map::proto::map_overlap_cc_proto
  modules::map::proto::map_parking_space_cc_proto
  modules::map::proto::map_pnc_junction_cc_proto
  modules::map::proto::map_road_cc_proto
  modules::map::proto::map_signal_cc_proto
  modules::map::proto::map_speed_bump_cc_proto
  modules::map::proto::map_stop_sign_cc_proto
  modules::map::proto::map_yield_sign_cc_proto
  modules::map::proto::map_rsu_cc_proto
)
add_library(modules::map::proto::map_cc_proto  ALIAS   modules_map_proto_map_cc_proto)

