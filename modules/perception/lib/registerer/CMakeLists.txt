cmake_minimum_required(VERSION 3.16)

project(modules_perception_lib_registerer)
message("${Green} [info] modules_perception_lib_registerer cmakelist ${ColourReset}")

add_library(modules_perception_lib_registerer_registerer  SHARED
  registerer.cc
)
set_target_properties(modules_perception_lib_registerer_registerer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lib_registerer_registerer
  cyber::cyber
)
add_library(modules::perception::lib::registerer::registerer  ALIAS   modules_perception_lib_registerer_registerer)

