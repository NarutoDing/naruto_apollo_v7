cmake_minimum_required(VERSION 3.16)

project(modules_map_relative_map)
message("${Green} [info] modules_map_relative_map cmakelist ${ColourReset}")

add_library(modules_map_relative_map_relative_map_lib  SHARED
  relative_map.cc
)
set_target_properties(modules_map_relative_map_relative_map_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_relative_map_relative_map_lib
  modules::map::relative_map::navigation_lane_lib
  modules::common::math::geometry
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::common::util::util
  modules::map::relative_map::common::relative_map_gflags
  modules::map::relative_map::proto::navigation_cc_proto
  modules::map::relative_map::proto::relative_map_config_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
)
add_library(modules::map::relative_map::relative_map_lib  ALIAS   modules_map_relative_map_relative_map_lib)

add_library(modules_map_relative_map_navigation_lane_lib  SHARED
  navigation_lane.cc
)
set_target_properties(modules_map_relative_map_navigation_lane_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_relative_map_navigation_lane_lib
  cyber::cyber
  modules::common::vehicle_state::vehicle_state_provider
  modules::common::vehicle_state::proto::vehicle_state_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::map::relative_map::common::relative_map_gflags
  modules::map::relative_map::proto::navigation_cc_proto
  modules::map::relative_map::proto::relative_map_config_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
)
add_library(modules::map::relative_map::navigation_lane_lib  ALIAS   modules_map_relative_map_navigation_lane_lib)

add_library(modules_map_relative_map_relative_map_component_lib  SHARED
  relative_map_component.cc
)
set_target_properties(modules_map_relative_map_relative_map_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_relative_map_relative_map_component_lib
  modules::map::relative_map::relative_map_lib
  cyber::cyber
  modules::common::adapters::adapter_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::map::relative_map::relative_map_component_lib  ALIAS   modules_map_relative_map_relative_map_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(librelative_map_component  SHARED
  ${virtual_cc}
)
set_target_properties(librelative_map_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(librelative_map_component
  modules::map::relative_map::relative_map_component_lib
)
