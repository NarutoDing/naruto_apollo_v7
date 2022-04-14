cmake_minimum_required(VERSION 3.16)

project(modules_contrib_cyber_bridge)
message("${Green} [info] modules_contrib_cyber_bridge cmakelist ${ColourReset}")

add_library(modules_contrib_cyber_bridge_bridge_server  SHARED
  server.cc
)
set_target_properties(modules_contrib_cyber_bridge_bridge_server  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_contrib_cyber_bridge_bridge_server
  modules::contrib::cyber_bridge::bridge_client
)
add_library(modules::contrib::cyber_bridge::bridge_server  ALIAS   modules_contrib_cyber_bridge_bridge_server)

add_library(modules_contrib_cyber_bridge_bridge_client  SHARED
  client.cc
)
set_target_properties(modules_contrib_cyber_bridge_bridge_client  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_contrib_cyber_bridge_bridge_client
  modules::contrib::cyber_bridge::bridge_clients
  modules::contrib::cyber_bridge::bridge_node
  ${boost}
)
add_library(modules::contrib::cyber_bridge::bridge_client  ALIAS   modules_contrib_cyber_bridge_bridge_client)

add_library(modules_contrib_cyber_bridge_bridge_clients  SHARED
  clients.cc
)
set_target_properties(modules_contrib_cyber_bridge_bridge_clients  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_contrib_cyber_bridge_bridge_clients
  modules::contrib::cyber_bridge::bridge_client_header
  ${boost}
)
add_library(modules::contrib::cyber_bridge::bridge_clients  ALIAS   modules_contrib_cyber_bridge_bridge_clients)

add_library(modules_contrib_cyber_bridge_bridge_node  SHARED
  node.cc
)
set_target_properties(modules_contrib_cyber_bridge_bridge_node  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_contrib_cyber_bridge_bridge_node
  modules::contrib::cyber_bridge::bridge_client_header
)
add_library(modules::contrib::cyber_bridge::bridge_node  ALIAS   modules_contrib_cyber_bridge_bridge_node)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_contrib_cyber_bridge_bridge_client_header  SHARED
  ${virtual_cc}
  client.h
)
set_target_properties(modules_contrib_cyber_bridge_bridge_client_header  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_contrib_cyber_bridge_bridge_client_header
  cyber::cyber
  ${boost}
)
add_library(modules::contrib::cyber_bridge::bridge_client_header  ALIAS   modules_contrib_cyber_bridge_bridge_client_header)

add_executable(cyber_bridge
  bridge.cc
)
target_link_libraries(cyber_bridge
  modules::contrib::cyber_bridge::bridge_server
  ${boost}
  ${gflags_LIBRARIES}
)
