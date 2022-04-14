cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_map_base_map)
message("${Green} [info] modules_localization_msf_local_map_base_map cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_map_base_map_base_map  SHARED
  base_map.cc
  base_map_config.cc
  base_map_matrix.cc
  base_map_node.cc
  base_map_node_index.cc
  base_map_pool.cc
)
set_target_properties(modules_localization_msf_local_map_base_map_base_map  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_map_base_map_base_map
  modules::common::util::util
  modules::localization::msf::common::util::util
  modules::localization::msf::common::util::base_map_cache
  modules::localization::msf::common::util::compression
  modules::localization::msf::common::util::system_utility
  ${boost}
  ${opencv}
  
)
add_library(modules::localization::msf::local_map::base_map::base_map  ALIAS   modules_localization_msf_local_map_base_map_base_map)

