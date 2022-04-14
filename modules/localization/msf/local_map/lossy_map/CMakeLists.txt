cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_map_lossy_map)
message("${Green} [info] modules_localization_msf_local_map_lossy_map cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_map_lossy_map_lossy_map  SHARED
  lossy_map_2d.cc
  lossy_map_config_2d.cc
  lossy_map_matrix_2d.cc
  lossy_map_pool_2d.cc
)
set_target_properties(modules_localization_msf_local_map_lossy_map_lossy_map  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_map_lossy_map_lossy_map
  modules::localization::msf::common::util::util
  modules::localization::msf::common::util::compression
  modules::localization::msf::local_map::base_map::base_map
  ${eigen}
  
)
add_library(modules::localization::msf::local_map::lossy_map::lossy_map  ALIAS   modules_localization_msf_local_map_lossy_map_lossy_map)

