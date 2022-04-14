cmake_minimum_required(VERSION 3.16)

project(modules_prediction_container_storytelling)
message("${Green} [info] modules_prediction_container_storytelling cmakelist ${ColourReset}")

add_library(modules_prediction_container_storytelling_storytelling_container  SHARED
  storytelling_container.cc
)
set_target_properties(modules_prediction_container_storytelling_storytelling_container  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_container_storytelling_storytelling_container
  modules::prediction::common::prediction_map
  modules::prediction::container::container
  modules::storytelling::proto::story_cc_proto
)
add_library(modules::prediction::container::storytelling::storytelling_container  ALIAS   modules_prediction_container_storytelling_storytelling_container)

