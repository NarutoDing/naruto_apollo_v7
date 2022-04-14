cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_tool_local_visualization_offline_visual)
message("${Green} [info] modules_localization_msf_local_tool_local_visualization_offline_visual cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_tool_local_visualization_offline_visual_offline_local_visualizer_lib  SHARED
  offline_local_visualizer.cc
)
set_target_properties(modules_localization_msf_local_tool_local_visualization_offline_visual_offline_local_visualizer_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_tool_local_visualization_offline_visual_offline_local_visualizer_lib
  cyber::common::log
  modules::common::util::util
  modules::localization::msf::common::io::common_io
  modules::localization::msf::local_pyramid_map::base_map::base_map
  modules::localization::msf::local_tool::local_visualization::engine::engine
  ${boost}
  ${absl}
)
add_library(modules::localization::msf::local_tool::local_visualization::offline_visual::offline_local_visualizer_lib  ALIAS   modules_localization_msf_local_tool_local_visualization_offline_visual_offline_local_visualizer_lib)

add_executable(offline_local_visualizer
  offline_local_visualizer_main.cc
)
target_link_libraries(offline_local_visualizer
  modules::localization::msf::local_tool::local_visualization::offline_visual::offline_local_visualizer_lib
  ${boost}
)
