cmake_minimum_required(VERSION 3.16)

project(modules_routing_tools)
message("${Green} [info] modules_routing_tools cmakelist ${ColourReset}")

add_executable(routing_dump
  routing_dump.cc
)
target_link_libraries(routing_dump
  modules::planning::proto::planning_cc_proto
  modules::routing::routing
)
add_executable(routing_cast
  routing_cast.cc
)
target_link_libraries(routing_cast
  modules::routing::routing
)
