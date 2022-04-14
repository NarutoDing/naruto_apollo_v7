cmake_minimum_required(VERSION 3.16)

project(cyber_mainboard)
message("${Green} [info] cyber_mainboard cmakelist ${ColourReset}")

add_executable(mainboard
  mainboard.cc
  module_argument.cc
  module_controller.cc
)
target_link_libraries(mainboard
  cyber::cyber_core
  cyber::proto::dag_conf_cc_proto
)
