cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_tool_local_visualization_engine)
message("${Green} [info] modules_localization_msf_local_tool_local_visualization_engine cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_tool_local_visualization_engine_engine  SHARED
  visualization_engine.cc
  visualization_manager.cc
)
set_target_properties(modules_localization_msf_local_tool_local_visualization_engine_engine  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_tool_local_visualization_engine_engine
  cyber::cyber
  modules::common::util::util
  modules::common::util::eigen_defs
  modules::localization::msf::common::io::common_io
  modules::localization::msf::local_pyramid_map::base_map::base_map
  ${boost}
  ${opencv}
)
add_library(modules::localization::msf::local_tool::local_visualization::engine::engine  ALIAS   modules_localization_msf_local_tool_local_visualization_engine_engine)

