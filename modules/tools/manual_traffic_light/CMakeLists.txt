cmake_minimum_required(VERSION 3.16)

project(modules_tools_manual_traffic_light)
message("${Green} [info] modules_tools_manual_traffic_light cmakelist ${ColourReset}")

add_library(modules_tools_manual_traffic_light_manual_traffic_light  SHARED
  manual_traffic_light.cc
)
set_target_properties(modules_tools_manual_traffic_light_manual_traffic_light  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_tools_manual_traffic_light_manual_traffic_light
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::color
  modules::common::util::message_util
  modules::map::hdmap::hdmap_util
  modules::perception::proto::traffic_light_detection_cc_proto
)
add_library(modules::tools::manual_traffic_light::manual_traffic_light  ALIAS   modules_tools_manual_traffic_light_manual_traffic_light)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libmanual_traffic_light_component  SHARED
  ${virtual_cc}
)
set_target_properties(libmanual_traffic_light_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libmanual_traffic_light_component
  modules::tools::manual_traffic_light::manual_traffic_light
)
