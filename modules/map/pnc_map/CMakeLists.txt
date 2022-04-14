cmake_minimum_required(VERSION 3.16)

project(modules_map_pnc_map)
message("${Green} [info] modules_map_pnc_map cmakelist ${ColourReset}")

add_library(modules_map_pnc_map_path  SHARED
  path.cc
)
set_target_properties(modules_map_pnc_map_path  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_pnc_map_path
  modules::common::math::math
  modules::map::hdmap::hdmap
  modules::map::hdmap::hdmap_util
  modules::map::proto::map_lane_cc_proto
)
add_library(modules::map::pnc_map::path  ALIAS   modules_map_pnc_map_path)

add_library(modules_map_pnc_map_route_segments  SHARED
  route_segments.cc
)
set_target_properties(modules_map_pnc_map_route_segments  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_pnc_map_route_segments
  modules::common::vehicle_state::proto::vehicle_state_cc_proto
  modules::map::hdmap::hdmap
  modules::map::pnc_map::path
  modules::routing::common::routing_gflags
  modules::routing::proto::routing_cc_proto
)
add_library(modules::map::pnc_map::route_segments  ALIAS   modules_map_pnc_map_route_segments)

add_library(modules_map_pnc_map_pnc_map  SHARED
  pnc_map.cc
)
set_target_properties(modules_map_pnc_map_pnc_map  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_pnc_map_pnc_map
  modules::map::pnc_map::path
  modules::map::pnc_map::route_segments
  modules::common::util::point_factory
  modules::common::vehicle_state::proto::vehicle_state_cc_proto
  modules::map::hdmap::hdmap
  modules::planning::common::planning_gflags
  modules::routing::common::routing_gflags
  
)
add_library(modules::map::pnc_map::pnc_map  ALIAS   modules_map_pnc_map_pnc_map)

cuda_add_library(modules_map_pnc_map_cuda_pnc_util
  cuda_util.cu
)
set_target_properties(modules_map_pnc_map_cuda_pnc_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_pnc_map_cuda_pnc_util
  cyber::common::log
  modules::common::math::geometry
  ${cuda}
)
add_library(modules::map::pnc_map::cuda_pnc_util  ALIAS   modules_map_pnc_map_cuda_pnc_util)

