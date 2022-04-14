cmake_minimum_required(VERSION 3.16)

project(modules_storytelling_story_tellers)
message("${Green} [info] modules_storytelling_story_tellers cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_storytelling_story_tellers_base_teller  SHARED
  ${virtual_cc}
  base_teller.h
)
set_target_properties(modules_storytelling_story_tellers_base_teller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_storytelling_story_tellers_base_teller
  modules::storytelling::proto::story_cc_proto
)
add_library(modules::storytelling::story_tellers::base_teller  ALIAS   modules_storytelling_story_tellers_base_teller)

add_library(modules_storytelling_story_tellers_close_to_junction_teller  SHARED
  close_to_junction_teller.cc
)
set_target_properties(modules_storytelling_story_tellers_close_to_junction_teller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_storytelling_story_tellers_close_to_junction_teller
  modules::storytelling::story_tellers::base_teller
  modules::common::adapters::adapter_gflags
  modules::map::hdmap::hdmap_util
  modules::planning::proto::planning_cc_proto
  modules::storytelling::frame_manager
  modules::storytelling::common::storytelling_gflags
  modules::storytelling::proto::storytelling_config_cc_proto
)
add_library(modules::storytelling::story_tellers::close_to_junction_teller  ALIAS   modules_storytelling_story_tellers_close_to_junction_teller)

