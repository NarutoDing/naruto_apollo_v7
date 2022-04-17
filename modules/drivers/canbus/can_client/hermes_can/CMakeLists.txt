cmake_minimum_required(VERSION 3.16)

project(modules_drivers_canbus_can_client_hermes_can)
message("${Green} [info] modules_drivers_canbus_can_client_hermes_can cmakelist ${ColourReset}")

add_library(modules_drivers_canbus_can_client_hermes_can_hermes_can_client  SHARED
  hermes_can_client.cc
)
set_target_properties(modules_drivers_canbus_can_client_hermes_can_hermes_can_client  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_can_client_hermes_can_hermes_can_client
  modules::common::proto::error_code_cc_proto
  modules::drivers::canbus::can_client::can_client
  #third_party::can_card_library::hermes_can::hermes_can
  ${hermes_can} #bug
)
add_library(modules::drivers::canbus::can_client::hermes_can::hermes_can_client  ALIAS   modules_drivers_canbus_can_client_hermes_can_hermes_can_client)

