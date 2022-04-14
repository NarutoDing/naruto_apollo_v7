cmake_minimum_required(VERSION 3.16)

project(modules_map_hdmap)
message("${Green} [info] modules_map_hdmap cmakelist ${ColourReset}")

add_library(modules_map_hdmap_hdmap  SHARED
  hdmap.cc
  hdmap_common.cc
  hdmap_impl.cc
)
set_target_properties(modules_map_hdmap_hdmap  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_hdmap
  cyber::common::file
  cyber::common::macros
  modules::common::configs::config_gflags
  modules::common::math::math
  modules::common::math::linear_interpolation
  modules::common::util::util
  modules::map::hdmap::adapter::opendrive_adapter
  modules::map::proto::map_cc_proto
  modules::map::relative_map::proto::navigation_cc_proto
  ${absl}
  ${glog_LIBRARIES}
)
add_library(modules::map::hdmap::hdmap  ALIAS   modules_map_hdmap_hdmap)

add_library(modules_map_hdmap_hdmap_util  SHARED
  hdmap_util.cc
)
set_target_properties(modules_map_hdmap_hdmap_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_hdmap_util
  modules::map::hdmap::hdmap
  cyber::common::file
  modules::common::configs::config_gflags
  modules::map::relative_map::proto::navigation_cc_proto
  ${absl}
)
add_library(modules::map::hdmap::hdmap_util  ALIAS   modules_map_hdmap_hdmap_util)

