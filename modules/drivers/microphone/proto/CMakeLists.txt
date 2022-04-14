cmake_minimum_required(VERSION 3.16)

project(modules_drivers_microphone_proto)
message("${Green} [info] modules_drivers_microphone_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/drivers/microphone/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_drivers_microphone_proto_audio_cc_proto  SHARED
  audio.pb.cc
)
set_target_properties(modules_drivers_microphone_proto_audio_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_microphone_proto_audio_cc_proto
  modules::drivers::microphone::proto::microphone_config_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::microphone::proto::audio_cc_proto  ALIAS   modules_drivers_microphone_proto_audio_cc_proto)

add_library(modules_drivers_microphone_proto_microphone_config_cc_proto  SHARED
  microphone_config.pb.cc
)
set_target_properties(modules_drivers_microphone_proto_microphone_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::microphone::proto::microphone_config_cc_proto  ALIAS   modules_drivers_microphone_proto_microphone_config_cc_proto)

