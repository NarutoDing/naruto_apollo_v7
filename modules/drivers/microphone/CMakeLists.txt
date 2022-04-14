cmake_minimum_required(VERSION 3.16)

project(modules_drivers_microphone)
message("${Green} [info] modules_drivers_microphone cmakelist ${ColourReset}")

add_library(modules_drivers_microphone_microphone_component_lib  SHARED
  microphone_component.cc
)
set_target_properties(modules_drivers_microphone_microphone_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_microphone_microphone_component_lib
  cyber::cyber
  modules::common::util::message_util
  modules::drivers::microphone::respeaker
  modules::drivers::microphone::proto::audio_cc_proto
  modules::drivers::microphone::proto::microphone_config_cc_proto
)
add_library(modules::drivers::microphone::microphone_component_lib  ALIAS   modules_drivers_microphone_microphone_component_lib)

add_library(modules_drivers_microphone_respeaker  SHARED
  respeaker.cc
)
set_target_properties(modules_drivers_microphone_respeaker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_microphone_respeaker
  cyber::cyber
  modules::drivers::microphone::proto::microphone_config_cc_proto
  ${portaudio}
)
add_library(modules::drivers::microphone::respeaker  ALIAS   modules_drivers_microphone_respeaker)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libmicrophone_component  SHARED
  ${virtual_cc}
)
set_target_properties(libmicrophone_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libmicrophone_component
  modules::drivers::microphone::microphone_component_lib
)
