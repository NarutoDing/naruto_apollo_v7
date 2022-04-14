cmake_minimum_required(VERSION 3.16)

project(modules_drivers_canbus_can_client_esd)
message("${Green} [info] modules_drivers_canbus_can_client_esd cmakelist ${ColourReset}")

add_library(modules_drivers_canbus_can_client_esd_esd_can_client  SHARED
  esd_can_client.cc
)
set_target_properties(modules_drivers_canbus_can_client_esd_esd_can_client  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::canbus::can_client::esd::esd_can_client  ALIAS   modules_drivers_canbus_can_client_esd_esd_can_client)

