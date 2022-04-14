cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_tool_map_creation_poses_interpolation)
message("${Green} [info] modules_localization_msf_local_tool_map_creation_poses_interpolation cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_tool_map_creation_poses_interpolation_poses_interpolation_lib  SHARED
  poses_interpolation.cc
)
set_target_properties(modules_localization_msf_local_tool_map_creation_poses_interpolation_poses_interpolation_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_tool_map_creation_poses_interpolation_poses_interpolation_lib
  modules::common::util::eigen_defs
  modules::localization::msf::common::io::common_io
  ${boost}
)
add_library(modules::localization::msf::local_tool::map_creation::poses_interpolation::poses_interpolation_lib  ALIAS   modules_localization_msf_local_tool_map_creation_poses_interpolation_poses_interpolation_lib)

