cmake_minimum_required(VERSION 3.16)

project(modules_routing_tools_routing_tester)
message("${Green} [info] modules_routing_tools_routing_tester cmakelist ${ColourReset}")

add_executable(routing_tester
  routing_tester.cc
  
)
target_link_libraries(routing_tester
  modules::routing::routing
)
