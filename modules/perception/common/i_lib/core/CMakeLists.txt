cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_i_lib_core)
message("${Green} [info] modules_perception_common_i_lib_core cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_i_lib_core_core  SHARED
  ${virtual_cc}
  i_alloc.h
  i_basic.h
  i_blas.h
  i_constant.h
  i_rand.h
)
set_target_properties(modules_perception_common_i_lib_core_core  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::common::i_lib::core::core  ALIAS   modules_perception_common_i_lib_core_core)

