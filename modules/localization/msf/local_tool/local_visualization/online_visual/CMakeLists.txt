cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_tool_local_visualization_online_visual)
message("${Green} [info] modules_localization_msf_local_tool_local_visualization_online_visual cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_tool_local_visualization_online_visual_online_visualizer_component_lib  SHARED
  online_visualizer_component.cc
)
set_target_properties(modules_localization_msf_local_tool_local_visualization_online_visual_online_visualizer_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_tool_local_visualization_online_visual_online_visualizer_component_lib
  cyber::cyber
  cyber::time::clock
  modules::common::adapters::adapter_gflags
  modules::common::math::math
  modules::common::proto::geometry_cc_proto
  modules::common::status::status
  modules::common::util::util
  modules::common::util::eigen_defs
  modules::drivers::proto::pointcloud_cc_proto
  modules::localization::common::localization_common
  modules::localization::msf::common::io::common_io
  modules::localization::msf::local_pyramid_map::base_map::base_map
  modules::localization::msf::local_tool::local_visualization::engine::engine
  modules::localization::proto::localization_cc_proto
  modules::localization::proto::localization_config_cc_proto
  ${boost}
  
  ${pcl}
)
add_library(modules::localization::msf::local_tool::local_visualization::online_visual::online_visualizer_component_lib  ALIAS   modules_localization_msf_local_tool_local_visualization_online_visual_online_visualizer_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(online_visualizer_compenont  SHARED
  ${virtual_cc}
)
set_target_properties(online_visualizer_compenont  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(online_visualizer_compenont
  modules::localization::msf::local_tool::local_visualization::online_visual::online_visualizer_component_lib
)
