cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_lane_change_decider)
message("${Green} [info] modules_planning_tasks_deciders_lane_change_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_lane_change_decider_lane_change_decider  SHARED
  lane_change_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_lane_change_decider_lane_change_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_lane_change_decider_lane_change_decider
  modules::map::pnc_map::route_segments
  modules::planning::common::planning_context
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::proto::planning_cc_proto
  modules::planning::tasks::deciders::decider_base
)
add_library(modules::planning::tasks::deciders::lane_change_decider::lane_change_decider  ALIAS   modules_planning_tasks_deciders_lane_change_decider_lane_change_decider)

