cmake_minimum_required(VERSION 3.16)

project(modules_audio_inference)
message("${Green} [info] modules_audio_inference cmakelist ${ColourReset}")

add_library(modules_audio_inference_moving_detection  SHARED
  moving_detection.cc
)
set_target_properties(modules_audio_inference_moving_detection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_audio_inference_moving_detection
  modules::audio::proto::audio_cc_proto
  ${fftw3}
)
add_library(modules::audio::inference::moving_detection  ALIAS   modules_audio_inference_moving_detection)

add_library(modules_audio_inference_direction_detection  SHARED
  direction_detection.cc
)
set_target_properties(modules_audio_inference_direction_detection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_audio_inference_direction_detection
  cyber::cyber
  modules::common::math::math_utils
  modules::common::proto::geometry_cc_proto
  ${libtorch}
  ${yaml}
  ${eigen}
)
add_library(modules::audio::inference::direction_detection  ALIAS   modules_audio_inference_direction_detection)

add_library(modules_audio_inference_siren_detection  SHARED
  siren_detection.cc
)
set_target_properties(modules_audio_inference_siren_detection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_audio_inference_siren_detection
  cyber::common::log
  modules::audio::common::audio_gflags
  ${libtorch}
)
add_library(modules::audio::inference::siren_detection  ALIAS   modules_audio_inference_siren_detection)

