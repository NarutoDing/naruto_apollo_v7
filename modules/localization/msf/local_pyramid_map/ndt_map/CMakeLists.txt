cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_pyramid_map_ndt_map)
message("${Green} [info] modules_localization_msf_local_pyramid_map_ndt_map cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_config  SHARED
  ndt_map_config.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_config  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_config
  modules::localization::msf::local_pyramid_map::base_map::base_map_config
  ${glog_LIBRARIES}
)
add_library(modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_config  ALIAS   modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_config)

add_library(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_matrix  SHARED
  ndt_map_matrix.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_matrix  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_matrix
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_config
  modules::localization::msf::common::util::util
  modules::localization::msf::local_pyramid_map::base_map::base_map_config
  modules::localization::msf::local_pyramid_map::base_map::base_map_matrix
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_matrix  ALIAS   modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_matrix)

add_library(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_matrix_handler  SHARED
  ndt_map_matrix_handler.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_matrix_handler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_matrix_handler
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_config
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_matrix
  modules::localization::msf::local_pyramid_map::base_map::base_map_node
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_matrix_handler  ALIAS   modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_matrix_handler)

add_library(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_node_config  SHARED
  ndt_map_node_config.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_node_config  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_node_config
  modules::localization::msf::local_pyramid_map::base_map::base_map_node_config
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_node_config  ALIAS   modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_node_config)

add_library(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_node  SHARED
  ndt_map_node.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_node  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_node
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_config
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_matrix
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_matrix_handler
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_node_config
  modules::localization::msf::common::util::util
  modules::localization::msf::local_pyramid_map::base_map::base_map_node
  ${glog_LIBRARIES}
  ${eigen}
)
add_library(modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_node  ALIAS   modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_node)

add_library(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_pool  SHARED
  ndt_map_pool.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_pool  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_pool
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_matrix
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_matrix_handler
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_node
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_node_config
  modules::localization::msf::common::util::util
  modules::localization::msf::local_pyramid_map::base_map::base_map_config
  modules::localization::msf::local_pyramid_map::base_map::base_map_pool
)
add_library(modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_pool  ALIAS   modules_localization_msf_local_pyramid_map_ndt_map_ndt_map_pool)

add_library(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map  SHARED
  ndt_map.cc
)
set_target_properties(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_pyramid_map_ndt_map_ndt_map
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_config
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_node
  modules::localization::msf::common::util::util
  modules::localization::msf::local_pyramid_map::base_map::base_map
)
add_library(modules::localization::msf::local_pyramid_map::ndt_map::ndt_map  ALIAS   modules_localization_msf_local_pyramid_map_ndt_map_ndt_map)

