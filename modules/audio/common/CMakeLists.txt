cmake_minimum_required(VERSION 3.16)

project(modules_audio_common)
message("${Green} [info] modules_audio_common cmakelist ${ColourReset}")

add_library(modules_audio_common_audio_gflags  SHARED
  audio_gflags.cc
)
set_target_properties(modules_audio_common_audio_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_audio_common_audio_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::audio::common::audio_gflags  ALIAS   modules_audio_common_audio_gflags)

add_library(modules_audio_common_audio_info  SHARED
  audio_info.cc
)
set_target_properties(modules_audio_common_audio_info  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_audio_common_audio_info
  modules::audio::common::audio_gflags
  modules::audio::proto::audio_cc_proto
  modules::drivers::microphone::proto::audio_cc_proto
  modules::drivers::microphone::proto::microphone_config_cc_proto
)
add_library(modules::audio::common::audio_info  ALIAS   modules_audio_common_audio_info)

add_library(modules_audio_common_message_process  SHARED
  message_process.cc
)
set_target_properties(modules_audio_common_message_process  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_audio_common_message_process
  modules::audio::common::audio_info
  modules::audio::inference::direction_detection
  modules::audio::inference::moving_detection
  modules::audio::inference::siren_detection
  modules::audio::proto::audio_cc_proto
  modules::audio::proto::audio_conf_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::drivers::microphone::proto::audio_cc_proto
)
add_library(modules::audio::common::message_process  ALIAS   modules_audio_common_message_process)

