cmake_minimum_required(VERSION 3.16)

project(modules_audio_tools)
message("${Green} [info] modules_audio_tools cmakelist ${ColourReset}")

add_executable(audio_offline_processing
  audio_offline_processing.cc
)
target_link_libraries(audio_offline_processing
  cyber::cyber
  modules::audio::common::audio_gflags
  modules::audio::common::message_process
  modules::audio::proto::audio_event_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
  ${boost}
)
