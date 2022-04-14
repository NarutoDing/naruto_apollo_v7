cmake_minimum_required(VERSION 3.16)

project(modules_storytelling_proto)
message("${Green} [info] modules_storytelling_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/storytelling/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_storytelling_proto_storytelling_config_cc_proto  SHARED
  storytelling_config.pb.cc
)
set_target_properties(modules_storytelling_proto_storytelling_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::storytelling::proto::storytelling_config_cc_proto  ALIAS   modules_storytelling_proto_storytelling_config_cc_proto)

add_library(modules_storytelling_proto_story_cc_proto  SHARED
  story.pb.cc
)
set_target_properties(modules_storytelling_proto_story_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_storytelling_proto_story_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::storytelling::proto::story_cc_proto  ALIAS   modules_storytelling_proto_story_cc_proto)

