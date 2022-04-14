cmake_minimum_required(VERSION 3.16)

project(modules_canbus_common)
message("${Green} [info] modules_canbus_common cmakelist ${ColourReset}")

add_library(modules_canbus_common_canbus_common  SHARED
  canbus_gflags.cc
)
set_target_properties(modules_canbus_common_canbus_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_common_canbus_common
  ${gflags_LIBRARIES}
)
add_library(modules::canbus::common::canbus_common  ALIAS   modules_canbus_common_canbus_common)

