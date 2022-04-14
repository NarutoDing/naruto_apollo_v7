cmake_minimum_required(VERSION 3.16)

project(cyber_blocker)
message("${Green} [info] cyber_blocker cmakelist ${ColourReset}")

add_library(cyber_blocker_blocker_manager  SHARED
  blocker_manager.cc
)
set_target_properties(cyber_blocker_blocker_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_blocker_blocker_manager
  cyber::blocker::blocker
)
add_library(cyber::blocker::blocker_manager  ALIAS   cyber_blocker_blocker_manager)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_blocker_blocker  SHARED
  ${virtual_cc}
  blocker.h
)
set_target_properties(cyber_blocker_blocker  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::blocker::blocker  ALIAS   cyber_blocker_blocker)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_blocker_intra_reader  SHARED
  ${virtual_cc}
  intra_reader.h
)
set_target_properties(cyber_blocker_intra_reader  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_blocker_intra_reader
  cyber::blocker::blocker_manager
)
add_library(cyber::blocker::intra_reader  ALIAS   cyber_blocker_intra_reader)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_blocker_intra_writer  SHARED
  ${virtual_cc}
  intra_writer.h
)
set_target_properties(cyber_blocker_intra_writer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_blocker_intra_writer
  cyber::blocker::blocker_manager
)
add_library(cyber::blocker::intra_writer  ALIAS   cyber_blocker_intra_writer)

