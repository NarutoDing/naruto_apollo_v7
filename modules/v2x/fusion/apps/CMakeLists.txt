cmake_minimum_required(VERSION 3.16)

project(modules_v2x_fusion_apps)
message("${Green} [info] modules_v2x_fusion_apps cmakelist ${ColourReset}")

add_library(modules_v2x_fusion_apps_v2x_fusion_component_lib  SHARED
  v2x_fusion_component.cc
)
set_target_properties(modules_v2x_fusion_apps_v2x_fusion_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_fusion_apps_v2x_fusion_component_lib
  cyber::component::component
  modules::common::adapters::adapter_gflags
  modules::v2x::fusion::apps::common::trans_tools
  modules::v2x::fusion::configs::ft_config_manager
  modules::v2x::fusion::configs::fusion_tracker_gflags
  modules::v2x::fusion::libs::fusion::fusion
  
)
add_library(modules::v2x::fusion::apps::v2x_fusion_component_lib  ALIAS   modules_v2x_fusion_apps_v2x_fusion_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libv2x_fusion_component  SHARED
  ${virtual_cc}
)
set_target_properties(libv2x_fusion_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libv2x_fusion_component
  modules::v2x::fusion::apps::v2x_fusion_component_lib
)
