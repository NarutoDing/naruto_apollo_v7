cmake_minimum_required(VERSION 3.16)

project(modules_localization_ndt_ndt_locator)
message("${Green} [info] modules_localization_ndt_ndt_locator cmakelist ${ColourReset}")

add_library(modules_localization_ndt_ndt_locator_ndt_lidar_locator  SHARED
  lidar_locator_ndt.cc
)
set_target_properties(modules_localization_ndt_ndt_locator_ndt_lidar_locator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_ndt_ndt_locator_ndt_lidar_locator
  cyber::cyber
  modules::common::math::math
  modules::common::monitor_log::monitor_log
  modules::common::util::perf_util
  modules::localization::common::localization_common
  modules::localization::msf::common::util::util
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map
  modules::localization::msf::local_pyramid_map::ndt_map::ndt_map_pool
  ${yaml}
  ${glog_LIBRARIES}
  ${eigen}
  ${pcl}
)
add_library(modules::localization::ndt::ndt_locator::ndt_lidar_locator  ALIAS   modules_localization_ndt_ndt_locator_ndt_lidar_locator)

