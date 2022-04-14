cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_common_util)
message("${Green} [info] modules_localization_msf_common_util cmakelist ${ColourReset}")

add_library(modules_localization_msf_common_util_compression  SHARED
  compression.cc
)
set_target_properties(modules_localization_msf_common_util_compression  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_common_util_compression
  cyber::cyber
  ${boost}
  ${eigen}
)
add_library(modules::localization::msf::common::util::compression  ALIAS   modules_localization_msf_common_util_compression)

add_library(modules_localization_msf_common_util_file_utility  SHARED
  file_utility.cc
)
set_target_properties(modules_localization_msf_common_util_file_utility  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_common_util_file_utility
  cyber::common::log
  ${boost}
  ${glog_LIBRARIES}
  ${eigen}
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(modules::localization::msf::common::util::file_utility  ALIAS   modules_localization_msf_common_util_file_utility)

add_library(modules_localization_msf_common_util_system_utility  SHARED
  system_utility.cc
)
set_target_properties(modules_localization_msf_common_util_system_utility  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_common_util_system_utility
  cyber::cyber
  ${boost}
  ${eigen}
)
add_library(modules::localization::msf::common::util::system_utility  ALIAS   modules_localization_msf_common_util_system_utility)

add_library(modules_localization_msf_common_util_frame_transform  SHARED
  frame_transform.cc
)
set_target_properties(modules_localization_msf_common_util_frame_transform  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_common_util_frame_transform
  cyber::cyber
  ${absl}
  ${eigen}
  ${proj}
)
add_library(modules::localization::msf::common::util::frame_transform  ALIAS   modules_localization_msf_common_util_frame_transform)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_localization_msf_common_util_util  SHARED
  ${virtual_cc}
  extract_ground_plane.h
  math_util.h
  rect2d.h
  time_conversion.h
  voxel_grid_covariance_hdmap.h
)
set_target_properties(modules_localization_msf_common_util_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_common_util_util
  cyber::cyber
  ${boost}
  ${eigen}
)
add_library(modules::localization::msf::common::util::util  ALIAS   modules_localization_msf_common_util_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_localization_msf_common_util_base_map_cache  SHARED
  ${virtual_cc}
  base_map_cache.h
)
set_target_properties(modules_localization_msf_common_util_base_map_cache  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_common_util_base_map_cache
  modules::common::util::lru_cache
)
add_library(modules::localization::msf::common::util::base_map_cache  ALIAS   modules_localization_msf_common_util_base_map_cache)

