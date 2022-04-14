cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_i_lib_pc)
message("${Green} [info] modules_perception_common_i_lib_pc cmakelist ${ColourReset}")

add_library(modules_perception_common_i_lib_pc_i_ground  SHARED
  i_ground.cc
)
set_target_properties(modules_perception_common_i_lib_pc_i_ground  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_i_lib_pc_i_ground
  modules::perception::common::i_lib::pc::i_struct_s
  modules::perception::common::i_lib::pc::i_util
  modules::perception::common::i_lib::algorithm::i_sort
  modules::perception::common::i_lib::core::core
  modules::perception::common::i_lib::da::i_ransac
  modules::perception::common::i_lib::geometry::i_plane
)
add_library(modules::perception::common::i_lib::pc::i_ground  ALIAS   modules_perception_common_i_lib_pc_i_ground)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_i_lib_pc_i_struct_s  SHARED
  ${virtual_cc}
  i_struct_s.h
)
set_target_properties(modules_perception_common_i_lib_pc_i_struct_s  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::common::i_lib::pc::i_struct_s  ALIAS   modules_perception_common_i_lib_pc_i_struct_s)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_i_lib_pc_i_util  SHARED
  ${virtual_cc}
  i_util.h
)
set_target_properties(modules_perception_common_i_lib_pc_i_util  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::common::i_lib::pc::i_util  ALIAS   modules_perception_common_i_lib_pc_i_util)

