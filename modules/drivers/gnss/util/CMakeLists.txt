cmake_minimum_required(VERSION 3.16)

project(modules_drivers_gnss_util)
message("${Green} [info] modules_drivers_gnss_util cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_gnss_util_gnss_util  SHARED
  ${virtual_cc}
  macros.h
  time_conversion.h
)
set_target_properties(modules_drivers_gnss_util_gnss_util  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::gnss::util::gnss_util  ALIAS   modules_drivers_gnss_util_gnss_util)

