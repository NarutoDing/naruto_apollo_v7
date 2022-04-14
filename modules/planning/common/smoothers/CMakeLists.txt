cmake_minimum_required(VERSION 3.16)

project(modules_planning_common_smoothers)
message("${Green} [info] modules_planning_common_smoothers cmakelist ${ColourReset}")

add_library(modules_planning_common_smoothers_smoother  SHARED
  smoother.cc
)
set_target_properties(modules_planning_common_smoothers_smoother  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_smoothers_smoother
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::proto::planning_cc_proto
)
add_library(modules::planning::common::smoothers::smoother  ALIAS   modules_planning_common_smoothers_smoother)

