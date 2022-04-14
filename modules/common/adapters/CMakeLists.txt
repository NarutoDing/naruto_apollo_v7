cmake_minimum_required(VERSION 3.16)

project(modules_common_adapters)
message("${Green} [info] modules_common_adapters cmakelist ${ColourReset}")

add_library(modules_common_adapters_adapter_gflags  SHARED
  adapter_gflags.cc
)
set_target_properties(modules_common_adapters_adapter_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_adapters_adapter_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::common::adapters::adapter_gflags  ALIAS   modules_common_adapters_adapter_gflags)

