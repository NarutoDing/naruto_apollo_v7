cmake_minimum_required(VERSION 3.16)

project(modules_drivers_canbus_common)
message("${Green} [info] modules_drivers_canbus_common cmakelist ${ColourReset}")

add_library(modules_drivers_canbus_common_canbus_common  SHARED
  byte.cc
)
set_target_properties(modules_drivers_canbus_common_canbus_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_common_canbus_common
  modules::drivers::canbus::sensor_gflags
)
add_library(modules::drivers::canbus::common::canbus_common  ALIAS   modules_drivers_canbus_common_canbus_common)

