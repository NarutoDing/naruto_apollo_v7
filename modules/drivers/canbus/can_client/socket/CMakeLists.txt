cmake_minimum_required(VERSION 3.16)

project(modules_drivers_canbus_can_client_socket)
message("${Green} [info] modules_drivers_canbus_can_client_socket cmakelist ${ColourReset}")

add_library(modules_drivers_canbus_can_client_socket_socket_can_client_raw  SHARED
  socket_can_client_raw.cc
)
set_target_properties(modules_drivers_canbus_can_client_socket_socket_can_client_raw  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_canbus_can_client_socket_socket_can_client_raw
  modules::common::proto::error_code_cc_proto
  modules::drivers::canbus::can_client::can_client
)
add_library(modules::drivers::canbus::can_client::socket::socket_can_client_raw  ALIAS   modules_drivers_canbus_can_client_socket_socket_can_client_raw)

