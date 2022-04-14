cmake_minimum_required(VERSION 3.16)

project(modules_common_latency_recorder)
message("${Green} [info] modules_common_latency_recorder cmakelist ${ColourReset}")

add_library(modules_common_latency_recorder_latency_recorder  SHARED
  latency_recorder.cc
)
set_target_properties(modules_common_latency_recorder_latency_recorder  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_latency_recorder_latency_recorder
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::latency_recorder::proto::latency_record_cc_proto
  modules::common::util::message_util
)
add_library(modules::common::latency_recorder::latency_recorder  ALIAS   modules_common_latency_recorder_latency_recorder)

