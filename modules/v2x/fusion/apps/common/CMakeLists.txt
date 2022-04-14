cmake_minimum_required(VERSION 3.16)

project(modules_v2x_fusion_apps_common)
message("${Green} [info] modules_v2x_fusion_apps_common cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_v2x_fusion_apps_common_ft_definitions  SHARED
  ${virtual_cc}
  ft_definitions.h
)
set_target_properties(modules_v2x_fusion_apps_common_ft_definitions  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_fusion_apps_common_ft_definitions
  modules::localization::proto::localization_cc_proto
  modules::perception::proto::perception_camera_cc_proto
  modules::v2x::fusion::libs::common::v2x_object
  modules::v2x::proto::v2x_obstacles_cc_proto
)
add_library(modules::v2x::fusion::apps::common::ft_definitions  ALIAS   modules_v2x_fusion_apps_common_ft_definitions)

add_library(modules_v2x_fusion_apps_common_trans_tools  SHARED
  trans_tools.cc
)
set_target_properties(modules_v2x_fusion_apps_common_trans_tools  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_fusion_apps_common_trans_tools
  modules::v2x::fusion::apps::common::ft_definitions
)
add_library(modules::v2x::fusion::apps::common::trans_tools  ALIAS   modules_v2x_fusion_apps_common_trans_tools)

