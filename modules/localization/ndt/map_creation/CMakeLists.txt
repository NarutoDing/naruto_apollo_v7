cmake_minimum_required(VERSION 3.16)

project(modules_localization_ndt_map_creation)
message("${Green} [info] modules_localization_ndt_map_creation cmakelist ${ColourReset}")

add_executable(ndt_map_creator
  ndt_map_creator.cc
)
target_link_libraries(ndt_map_creator
  cyber::cyber
  modules::localization::msf::common::io::common_io
  modules::localization::msf::common::util::util
  modules::localization::msf::common::util::system_utility
  modules::localization::msf::local_pyramid_map::base_map::base_map
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_pool
  ${boost}
  ${absl}
  ${eigen}
)
