cmake_minimum_required(VERSION 3.16)

project(modules_v2x_fusion_libs_fusion)
message("${Green} [info] modules_v2x_fusion_libs_fusion cmakelist ${ColourReset}")

add_library(modules_v2x_fusion_libs_fusion_fusion  SHARED
  fusion.cc
)
set_target_properties(modules_v2x_fusion_libs_fusion_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_fusion_libs_fusion_fusion
  modules::v2x::fusion::libs::fusion::km
  modules::v2x::fusion::configs::ft_config_manager
  modules::v2x::fusion::libs::common::v2x_object
  ${eigen}
)
add_library(modules::v2x::fusion::libs::fusion::fusion  ALIAS   modules_v2x_fusion_libs_fusion_fusion)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_v2x_fusion_libs_fusion_km  SHARED
  ${virtual_cc}
  km.h
)
set_target_properties(modules_v2x_fusion_libs_fusion_km  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_fusion_libs_fusion_km
  ${eigen}
)
add_library(modules::v2x::fusion::libs::fusion::km  ALIAS   modules_v2x_fusion_libs_fusion_km)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_v2x_fusion_libs_fusion_test_tools  SHARED
  ${virtual_cc}
  test_tools.h
)
set_target_properties(modules_v2x_fusion_libs_fusion_test_tools  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_fusion_libs_fusion_test_tools
  modules::v2x::fusion::libs::common::v2x_object
)
add_library(modules::v2x::fusion::libs::fusion::test_tools  ALIAS   modules_v2x_fusion_libs_fusion_test_tools)

