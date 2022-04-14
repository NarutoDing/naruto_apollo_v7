cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_pyramid_map_base_map)
message("${Green} [info] modules_localization_msf_local_pyramid_map_base_map cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_pyramid_map_base_map_base_map_config  SHARED
  base_map_config.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_base_map_base_map_config  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_base_map_base_map_config
  cyber::common::common
  modules::common::util::util
  modules::localization::msf::common::util::util
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::base_map::base_map_config  ALIAS   modules_localization_msf_local_pyramid_map_base_map_base_map_config)

add_library(modules_localization_msf_local_pyramid_map_base_map_base_map_matrix  SHARED
  base_map_matrix.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_base_map_base_map_matrix  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_base_map_base_map_matrix
  cyber::common::common
  ${glog_LIBRARIES}
  ${eigen}
  ${opencv}
  
)
add_library(modules::localization::msf::local_pyramid_map::base_map::base_map_matrix  ALIAS   modules_localization_msf_local_pyramid_map_base_map_base_map_matrix)

add_library(modules_localization_msf_local_pyramid_map_base_map_base_map_node_index  SHARED
  base_map_node_index.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_base_map_base_map_node_index  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_base_map_base_map_node_index
  modules::localization::msf::local_pyramid_map::base_map::base_map_config
  cyber::common::common
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::base_map::base_map_node_index  ALIAS   modules_localization_msf_local_pyramid_map_base_map_base_map_node_index)

add_library(modules_localization_msf_local_pyramid_map_base_map_base_map_node_config  SHARED
  base_map_node_config.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_base_map_base_map_node_config  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_base_map_base_map_node_config
  modules::localization::msf::local_pyramid_map::base_map::base_map_node_index
  cyber::common::common
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::base_map::base_map_node_config  ALIAS   modules_localization_msf_local_pyramid_map_base_map_base_map_node_config)

add_library(modules_localization_msf_local_pyramid_map_base_map_base_map_node  SHARED
  base_map_node.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_base_map_base_map_node  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_base_map_base_map_node
  modules::localization::msf::local_pyramid_map::base_map::base_map_config
  modules::localization::msf::local_pyramid_map::base_map::base_map_matrix
  modules::localization::msf::local_pyramid_map::base_map::base_map_node_config
  modules::localization::msf::local_pyramid_map::base_map::base_map_node_index
  cyber::common::common
  modules::localization::msf::common::util::util
  modules::localization::msf::common::util::compression
  modules::localization::msf::common::util::file_utility
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::base_map::base_map_node  ALIAS   modules_localization_msf_local_pyramid_map_base_map_base_map_node)

add_library(modules_localization_msf_local_pyramid_map_base_map_base_map_pool  SHARED
  base_map_pool.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_base_map_base_map_pool  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_base_map_base_map_pool
  modules::localization::msf::local_pyramid_map::base_map::base_map_config
  modules::localization::msf::local_pyramid_map::base_map::base_map_node
  modules::localization::msf::local_pyramid_map::base_map::base_map_node_index
  cyber::common::common
  modules::localization::msf::common::util::util
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::base_map::base_map_pool  ALIAS   modules_localization_msf_local_pyramid_map_base_map_base_map_pool)

add_library(modules_localization_msf_local_pyramid_map_base_map_base_map  SHARED
  base_map.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_base_map_base_map  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_base_map_base_map
  modules::localization::msf::local_pyramid_map::base_map::base_map_config
  modules::localization::msf::local_pyramid_map::base_map::base_map_node
  modules::localization::msf::local_pyramid_map::base_map::base_map_node_index
  modules::localization::msf::local_pyramid_map::base_map::base_map_pool
  cyber::common::common
  modules::localization::msf::common::util::util
  modules::localization::msf::common::util::base_map_cache
  modules::localization::msf::common::util::file_utility
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::base_map::base_map  ALIAS   modules_localization_msf_local_pyramid_map_base_map_base_map)

