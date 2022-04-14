cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_common)
message("${Green} [info] modules_perception_radar_common cmakelist ${ColourReset}")

add_library(modules_perception_radar_common_radar_util  SHARED
  radar_util.cc
)
set_target_properties(modules_perception_radar_common_radar_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_common_radar_util
  modules::perception::base::base
  ${eigen}
)
add_library(modules::perception::radar::common::radar_util  ALIAS   modules_perception_radar_common_radar_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_radar_common_types  SHARED
  ${virtual_cc}
  types.h
)
set_target_properties(modules_perception_radar_common_types  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::radar::common::types  ALIAS   modules_perception_radar_common_types)

