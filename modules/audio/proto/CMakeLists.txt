cmake_minimum_required(VERSION 3.16)

project(modules_audio_proto)
message("${Green} [info] modules_audio_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/audio/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_audio_proto_audio_conf_cc_proto  SHARED
  audio_conf.pb.cc
)
set_target_properties(modules_audio_proto_audio_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::audio::proto::audio_conf_cc_proto  ALIAS   modules_audio_proto_audio_conf_cc_proto)

add_library(modules_audio_proto_audio_cc_proto  SHARED
  audio.pb.cc
)
set_target_properties(modules_audio_proto_audio_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_audio_proto_audio_cc_proto
  modules::audio::proto::audio_common_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::audio::proto::audio_cc_proto  ALIAS   modules_audio_proto_audio_cc_proto)

add_library(modules_audio_proto_audio_common_cc_proto  SHARED
  audio_common.pb.cc
)
set_target_properties(modules_audio_proto_audio_common_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::audio::proto::audio_common_cc_proto  ALIAS   modules_audio_proto_audio_common_cc_proto)

add_library(modules_audio_proto_audio_event_cc_proto  SHARED
  audio_event.pb.cc
)
set_target_properties(modules_audio_proto_audio_event_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_audio_proto_audio_event_cc_proto
  modules::audio::proto::audio_common_cc_proto
  modules::common::proto::header_cc_proto
  modules::localization::proto::pose_cc_proto
)
add_library(modules::audio::proto::audio_event_cc_proto  ALIAS   modules_audio_proto_audio_event_cc_proto)

