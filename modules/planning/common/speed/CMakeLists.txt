cmake_minimum_required(VERSION 3.16)

project(modules_planning_common_speed)
message("${Green} [info] modules_planning_common_speed cmakelist ${ColourReset}")

add_library(modules_planning_common_speed_st_point  SHARED
  st_point.cc
)
set_target_properties(modules_planning_common_speed_st_point  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_speed_st_point
  modules::common::math::math
  ${gflags_LIBRARIES}
)
add_library(modules::planning::common::speed::st_point  ALIAS   modules_planning_common_speed_st_point)

add_library(modules_planning_common_speed_st_boundary  SHARED
  st_boundary.cc
)
set_target_properties(modules_planning_common_speed_st_boundary  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_speed_st_boundary
  modules::planning::common::speed::st_point
  cyber::common::log
  modules::planning::common::planning_gflags
  modules::planning::proto::planning_cc_proto
  
)
add_library(modules::planning::common::speed::st_boundary  ALIAS   modules_planning_common_speed_st_boundary)

add_library(modules_planning_common_speed_speed_data  SHARED
  speed_data.cc
)
set_target_properties(modules_planning_common_speed_speed_data  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_speed_speed_data
  modules::planning::common::speed::st_point
  modules::common::math::math
  modules::common::proto::pnc_point_cc_proto
  modules::common::util::util
  modules::common::util::point_factory
  modules::common::util::string_util
  modules::planning::common::planning_context
  modules::planning::common::planning_gflags
  modules::planning::proto::planning_cc_proto
  ${gflags_LIBRARIES}
)
add_library(modules::planning::common::speed::speed_data  ALIAS   modules_planning_common_speed_speed_data)

