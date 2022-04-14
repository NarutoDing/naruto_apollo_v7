cmake_minimum_required(VERSION 3.16)

project(modules_planning_planner)
message("${Green} [info] modules_planning_planner cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_planner_planner  SHARED
  ${virtual_cc}
  planner.h
)
set_target_properties(modules_planning_planner_planner  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_planner_planner
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::reference_line_info
  modules::planning::proto::planning_cc_proto
  modules::planning::scenarios::scenario
  modules::planning::scenarios::scenario_manager
)
add_library(modules::planning::planner::planner  ALIAS   modules_planning_planner_planner)

add_library(modules_planning_planner_planner_dispatcher  SHARED
  navi_planner_dispatcher.cc
  on_lane_planner_dispatcher.cc
  planner_dispatcher.cc
)
set_target_properties(modules_planning_planner_planner_dispatcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_planner_planner_dispatcher
  modules::common::status::status
  modules::common::util::util
  modules::planning::planner::lattice::lattice_planner
  modules::planning::planner::navi::navi_planner
  modules::planning::planner::public_road::public_road_planner
  modules::planning::planner::rtk::rtk_planner
  modules::planning::proto::planning_cc_proto
)
add_library(modules::planning::planner::planner_dispatcher  ALIAS   modules_planning_planner_planner_dispatcher)

