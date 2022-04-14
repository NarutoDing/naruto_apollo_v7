cmake_minimum_required(VERSION 3.16)

project(cyber_io)
message("${Green} [info] cyber_io cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_io_io  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_io_io  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_io_io
  cyber::io::poll_data
  cyber::io::poll_handler
  cyber::io::poller
  cyber::io::session
)
add_library(cyber::io::io  ALIAS   cyber_io_io)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_io_poll_data  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_io_poll_data  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::io::poll_data  ALIAS   cyber_io_poll_data)

add_library(cyber_io_poll_handler  SHARED
  poll_handler.cc
)
set_target_properties(cyber_io_poll_handler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_io_poll_handler
  cyber::io::poll_data
  cyber::io::poller
  cyber::common::log
  cyber::croutine::croutine
)
add_library(cyber::io::poll_handler  ALIAS   cyber_io_poll_handler)

add_library(cyber_io_poller  SHARED
  poller.cc
)
set_target_properties(cyber_io_poller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_io_poller
  cyber::io::poll_data
  cyber::base::atomic_rw_lock
  cyber::common::log
  cyber::common::macros
  cyber::scheduler::scheduler_factory
  cyber::time::time
)
add_library(cyber::io::poller  ALIAS   cyber_io_poller)

add_library(cyber_io_session  SHARED
  session.cc
)
set_target_properties(cyber_io_session  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_io_session
  cyber::io::poll_handler
  cyber::common::log
)
add_library(cyber::io::session  ALIAS   cyber_io_session)

add_executable(tcp_echo_client
  example/tcp_echo_client.cc
)
target_link_libraries(tcp_echo_client
  cyber::cyber_core
)
add_executable(tcp_echo_server
  example/tcp_echo_server.cc
)
target_link_libraries(tcp_echo_server
  cyber::cyber_core
)
add_executable(udp_echo_client
  example/udp_echo_client.cc
)
target_link_libraries(udp_echo_client
  cyber::cyber_core
)
add_executable(udp_echo_server
  example/udp_echo_server.cc
)
target_link_libraries(udp_echo_server
  cyber::cyber_core
)
