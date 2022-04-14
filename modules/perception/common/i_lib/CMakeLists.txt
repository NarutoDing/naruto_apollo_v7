cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_i_lib)
message("${Green} [info] modules_perception_common_i_lib cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_common_i_lib_i_lib  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_common_i_lib_i_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_i_lib_i_lib
  modules::perception::common::i_lib::algorithm::i_sort
  modules::perception::common::i_lib::core::core
  modules::perception::common::i_lib::da::i_ransac
  modules::perception::common::i_lib::geometry::i_plane
  modules::perception::common::i_lib::pc::i_ground
)
add_library(modules::perception::common::i_lib::i_lib  ALIAS   modules_perception_common_i_lib_i_lib)

