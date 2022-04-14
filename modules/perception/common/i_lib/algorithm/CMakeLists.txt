cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_i_lib_algorithm)
message("${Green} [info] modules_perception_common_i_lib_algorithm cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_i_lib_algorithm_i_sort  SHARED
  ${virtual_cc}
  i_sort.h
)
set_target_properties(modules_perception_common_i_lib_algorithm_i_sort  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_i_lib_algorithm_i_sort
  cyber::cyber
)
add_library(modules::perception::common::i_lib::algorithm::i_sort  ALIAS   modules_perception_common_i_lib_algorithm_i_sort)

