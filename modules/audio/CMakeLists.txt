cmake_minimum_required(VERSION 3.16)

project(modules_audio)
message("${Green} [info] modules_audio cmakelist ${ColourReset}")

add_library(modules_audio_audio_component_lib  SHARED
  audio_component.cc
)
set_target_properties(modules_audio_audio_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_audio_audio_component_lib
  cyber::cyber
  modules::audio::common::message_process
  modules::localization::proto::localization_cc_proto
  
)
add_library(modules::audio::audio_component_lib  ALIAS   modules_audio_audio_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libaudio_component  SHARED
  ${virtual_cc}
)
set_target_properties(libaudio_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libaudio_component
  modules::audio::audio_component_lib
)
