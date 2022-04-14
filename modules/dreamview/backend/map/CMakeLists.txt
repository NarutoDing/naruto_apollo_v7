cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_map)
message("${Green} [info] modules_dreamview_backend_map cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_map_map_service  SHARED
  map_service.cc
)
set_target_properties(modules_dreamview_backend_map_map_service  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_map_map_service
  modules::common::util::json_util
  modules::dreamview::proto::simulation_world_cc_proto
  modules::map::hdmap::hdmap_util
  modules::map::pnc_map::pnc_map
  ${boost}
  ${json}
  ${glog_LIBRARIES}
)
add_library(modules::dreamview::backend::map::map_service  ALIAS   modules_dreamview_backend_map_map_service)

