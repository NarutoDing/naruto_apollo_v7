cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_map_ndt_map)
message("${Green} [info] modules_localization_msf_local_map_ndt_map cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_map_ndt_map_ndt_map  SHARED
  ndt_map.cc
  ndt_map_config.cc
  ndt_map_matrix.cc
  ndt_map_node.cc
  ndt_map_pool.cc
)
set_target_properties(modules_localization_msf_local_map_ndt_map_ndt_map  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_map_ndt_map_ndt_map
  modules::localization::msf::common::util::util
  modules::localization::msf::common::util::base_map_cache
  modules::localization::msf::common::util::compression
  modules::localization::msf::local_map::base_map::base_map
  ${eigen}
  
)
add_library(modules::localization::msf::local_map::ndt_map::ndt_map  ALIAS   modules_localization_msf_local_map_ndt_map_ndt_map)

