cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_map_lossless_map)
message("${Green} [info] modules_localization_msf_local_map_lossless_map cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_map_lossless_map_lossless_map  SHARED
  lossless_map.cc
  lossless_map_config.cc
  lossless_map_matrix.cc
  lossless_map_node.cc
  lossless_map_pool.cc
)
set_target_properties(modules_localization_msf_local_map_lossless_map_lossless_map  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_map_lossless_map_lossless_map
  modules::localization::msf::common::util::util
  modules::localization::msf::common::util::base_map_cache
  modules::localization::msf::common::util::compression
  modules::localization::msf::local_map::base_map::base_map
  ${eigen}
  
)
add_library(modules::localization::msf::local_map::lossless_map::lossless_map  ALIAS   modules_localization_msf_local_map_lossless_map_lossless_map)

