cmake_minimum_required(VERSION 3.16)

project(modules_storytelling)
message("${Green} [info] modules_storytelling cmakelist ${ColourReset}")

add_library(modules_storytelling_frame_manager  SHARED
  frame_manager.cc
)
set_target_properties(modules_storytelling_frame_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_storytelling_frame_manager
  cyber::cyber
  modules::common::monitor_log::monitor_log
)
add_library(modules::storytelling::frame_manager  ALIAS   modules_storytelling_frame_manager)

add_library(modules_storytelling_storytelling_lib  SHARED
  storytelling.cc
)
set_target_properties(modules_storytelling_storytelling_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_storytelling_storytelling_lib
  cyber::cyber
  modules::storytelling::story_tellers::close_to_junction_teller
)
add_library(modules::storytelling::storytelling_lib  ALIAS   modules_storytelling_storytelling_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libstorytelling_component  SHARED
  ${virtual_cc}
)
set_target_properties(libstorytelling_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libstorytelling_component
  modules::storytelling::storytelling_lib
)
