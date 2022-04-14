cmake_minimum_required(VERSION 3.16)

project(modules_localization_common)
message("${Green} [info] modules_localization_common cmakelist ${ColourReset}")

add_library(modules_localization_common_localization_common  SHARED
  localization_gflags.cc
)
set_target_properties(modules_localization_common_localization_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_common_localization_common
  cyber::cyber
  modules::dreamview::backend::hmi::vehicle_manager
  modules::localization::proto::localization_cc_proto
)
add_library(modules::localization::common::localization_common  ALIAS   modules_localization_common_localization_common)

