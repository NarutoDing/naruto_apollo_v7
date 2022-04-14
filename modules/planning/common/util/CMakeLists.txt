cmake_minimum_required(VERSION 3.16)

project(modules_planning_common_util)
message("${Green} [info] modules_planning_common_util cmakelist ${ColourReset}")

add_library(modules_planning_common_util_util_lib  SHARED
  util.cc
)
set_target_properties(modules_planning_common_util_util_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_util_util_lib
  cyber::common::log
  modules::common::util::util
  modules::common::vehicle_state::vehicle_state_provider
  modules::common::vehicle_state::proto::vehicle_state_cc_proto
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::proto::planning_cc_proto
  modules::routing::routing
)
add_library(modules::planning::common::util::util_lib  ALIAS   modules_planning_common_util_util_lib)

add_library(modules_planning_common_util_common_lib  SHARED
  common.cc
)
set_target_properties(modules_planning_common_util_common_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_util_common_lib
  cyber::common::log
  modules::common::util::util
  modules::planning::common::frame
  modules::planning::common::reference_line_info
)
add_library(modules::planning::common::util::common_lib  ALIAS   modules_planning_common_util_common_lib)

add_library(modules_planning_common_util_math_util_lib  SHARED
  math_util.cc
)
set_target_properties(modules_planning_common_util_math_util_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_util_math_util_lib
  cyber::common::log
  modules::common::math::math
)
add_library(modules::planning::common::util::math_util_lib  ALIAS   modules_planning_common_util_math_util_lib)

