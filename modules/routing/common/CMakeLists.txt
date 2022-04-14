cmake_minimum_required(VERSION 3.16)

project(modules_routing_common)
message("${Green} [info] modules_routing_common cmakelist ${ColourReset}")

add_library(modules_routing_common_routing_gflags  SHARED
  routing_gflags.cc
)
set_target_properties(modules_routing_common_routing_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_routing_common_routing_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::routing::common::routing_gflags  ALIAS   modules_routing_common_routing_gflags)

