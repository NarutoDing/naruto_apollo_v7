cmake_minimum_required(VERSION 3.16)

project(modules_bridge_test)
message("${Green} [info] modules_bridge_test cmakelist ${ColourReset}")

add_executable(bridge_receiver_test
  bridge_receiver_test.cc
)
target_link_libraries(bridge_receiver_test
  cyber::cyber
  modules::bridge::udp_bridge
  modules::bridge::common::udp_listener
)
add_executable(bridge_sender_test
  bridge_sender_test.cc
)
target_link_libraries(bridge_sender_test
  cyber::cyber
  modules::bridge::udp_bridge
)
