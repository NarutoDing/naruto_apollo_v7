cmake_minimum_required(VERSION 3.16)

project(modules_planning_tools)
message("${Green} [info] modules_planning_tools cmakelist ${ColourReset}")

add_executable(pad_terminal
  pad_terminal.cc
)
target_link_libraries(pad_terminal
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::planning::common::planning_gflags
  modules::planning::proto::pad_msg_cc_proto
  modules::planning::proto::planning_config_cc_proto
  ${gflags_LIBRARIES}
)
add_executable(inference_demo
  inference_demo.cc
)
target_link_libraries(inference_demo
  ${libtorch}
  ${gflags_LIBRARIES}
)
