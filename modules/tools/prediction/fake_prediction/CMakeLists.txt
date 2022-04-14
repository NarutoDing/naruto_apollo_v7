cmake_minimum_required(VERSION 3.16)

project(modules_tools_prediction_fake_prediction)
message("${Green} [info] modules_tools_prediction_fake_prediction cmakelist ${ColourReset}")

add_library(libfake_prediction_component  SHARED
  fake_prediction.cc
)
set_target_properties(libfake_prediction_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libfake_prediction_component
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::prediction::proto::prediction_obstacle_cc_proto
)
