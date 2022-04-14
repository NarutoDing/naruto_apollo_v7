cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_path_decider)
message("${Green} [info] modules_planning_tasks_deciders_path_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_path_decider_path_decider  SHARED
  path_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_path_decider_path_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_path_decider_path_decider
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::path_decision
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::tasks::task
)
add_library(modules::planning::tasks::deciders::path_decider::path_decider  ALIAS   modules_planning_tasks_deciders_path_decider_path_decider)

