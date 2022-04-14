cmake_minimum_required(VERSION 3.16)

project(modules_map_relative_map_tools)
message("${Green} [info] modules_map_relative_map_tools cmakelist ${ColourReset}")

add_executable(navigation_dummy
  navigation_dummy.cc
)
target_link_libraries(navigation_dummy
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::util
  modules::map::relative_map::relative_map_lib
)
add_executable(navigator
  navigator.cc
)
target_link_libraries(navigator
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::util
  modules::map::relative_map::relative_map_lib
  modules::map::relative_map::proto::navigator_config_cc_proto
  ${json}
)
