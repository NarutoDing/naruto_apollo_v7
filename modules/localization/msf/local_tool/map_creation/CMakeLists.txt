cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_tool_map_creation)
message("${Green} [info] modules_localization_msf_local_tool_map_creation cmakelist ${ColourReset}")

add_executable(lossless_map_creator
  lossless_map_creator.cc
)
target_link_libraries(lossless_map_creator
  cyber::common::file
  modules::localization::msf::common::io::common_io
  modules::localization::msf::common::util::util
  modules::localization::msf::local_pyramid_map::base_map::base_map
  modules::localization::msf::local_pyramid_map::pyramid_map::pyramid_map
  modules::localization::msf::local_pyramid_map::pyramid_map::pyramid_map_pool
  ${boost}
  ${absl}
)
add_executable(lossless_map_to_lossy_map
  lossless_map_to_lossy_map.cc
)
target_link_libraries(lossless_map_to_lossy_map
  modules::localization::msf::local_pyramid_map::base_map::base_map
  modules::localization::msf::local_pyramid_map::pyramid_map::pyramid_map
  modules::localization::msf::local_pyramid_map::pyramid_map::pyramid_map_pool
  ${boost}
)
add_executable(poses_interpolator
  poses_interpolator.cc
)
target_link_libraries(poses_interpolator
  modules::localization::msf::local_tool::map_creation::poses_interpolation::poses_interpolation_lib
)
