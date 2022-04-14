cmake_minimum_required(VERSION 3.16)

project(modules_drivers_canbus_can_client_fake)
message("${Green} [info] modules_drivers_canbus_can_client_fake cmakelist ${ColourReset}")

add_library(modules_drivers_canbus_can_client_fake_fake_can_client  SHARED
  fake_can_client.cc
)
set_target_properties(modules_drivers_canbus_can_client_fake_fake_can_client  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_can_client_fake_fake_can_client
  modules::common::proto::error_code_cc_proto
  modules::drivers::canbus::can_client::can_client
)
add_library(modules::drivers::canbus::can_client::fake::fake_can_client  ALIAS   modules_drivers_canbus_can_client_fake_fake_can_client)

