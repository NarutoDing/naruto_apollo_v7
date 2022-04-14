cmake_minimum_required(VERSION 3.16)

project(modules_v2x_fusion_libs_common)
message("${Green} [info] modules_v2x_fusion_libs_common cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_v2x_fusion_libs_common_v2x_object  SHARED
  ${virtual_cc}
  v2x_object.h
)
set_target_properties(modules_v2x_fusion_libs_common_v2x_object  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_fusion_libs_common_v2x_object
  modules::perception::base::base_type
  modules::perception::base::box
  modules::perception::base::object
  ${absl}
)
add_library(modules::v2x::fusion::libs::common::v2x_object  ALIAS   modules_v2x_fusion_libs_common_v2x_object)

