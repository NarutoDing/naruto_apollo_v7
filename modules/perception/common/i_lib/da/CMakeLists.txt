cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_i_lib_da)
message("${Green} [info] modules_perception_common_i_lib_da cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_i_lib_da_i_ransac  SHARED
  ${virtual_cc}
  i_ransac.h
)
set_target_properties(modules_perception_common_i_lib_da_i_ransac  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::common::i_lib::da::i_ransac  ALIAS   modules_perception_common_i_lib_da_i_ransac)

