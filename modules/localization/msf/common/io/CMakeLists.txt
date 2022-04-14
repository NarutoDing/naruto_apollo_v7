cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_common_io)
message("${Green} [info] modules_localization_msf_common_io cmakelist ${ColourReset}")

add_library(modules_localization_msf_common_io_common_io  SHARED
  velodyne_utility.cc
)
set_target_properties(modules_localization_msf_common_io_common_io  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_common_io_common_io
  cyber::cyber
  modules::common::util::eigen_defs
  ${yaml}
  ${pcl}
  
)
add_library(modules::localization::msf::common::io::common_io  ALIAS   modules_localization_msf_common_io_common_io)

