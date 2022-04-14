cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_dummy)
message("${Green} [info] modules_perception_fusion_lib_dummy cmakelist ${ColourReset}")

add_library(modules_perception_fusion_lib_dummy_dummy_algorithms  SHARED
  dummy_algorithms.cc
)
set_target_properties(modules_perception_fusion_lib_dummy_dummy_algorithms  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_dummy_dummy_algorithms
  cyber::cyber
  modules::perception::fusion::base::base
  modules::perception::fusion::lib::interface::interface
  modules::perception::fusion::lib::interface::base_fusion_system
  ${eigen}
)
add_library(modules::perception::fusion::lib::dummy::dummy_algorithms  ALIAS   modules_perception_fusion_lib_dummy_dummy_algorithms)

