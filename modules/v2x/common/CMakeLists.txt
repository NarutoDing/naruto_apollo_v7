cmake_minimum_required(VERSION 3.16)

project(modules_v2x_common)
message("${Green} [info] modules_v2x_common cmakelist ${ColourReset}")

add_library(modules_v2x_common_v2x_proxy_gflags  SHARED
  v2x_proxy_gflags.cc
)
set_target_properties(modules_v2x_common_v2x_proxy_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_common_v2x_proxy_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::v2x::common::v2x_proxy_gflags  ALIAS   modules_v2x_common_v2x_proxy_gflags)

