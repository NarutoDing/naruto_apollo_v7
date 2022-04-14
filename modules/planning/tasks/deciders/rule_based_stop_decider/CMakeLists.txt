cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_rule_based_stop_decider)
message("${Green} [info] modules_planning_tasks_deciders_rule_based_stop_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_rule_based_stop_decider_rule_based_stop_decider  SHARED
  rule_based_stop_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_rule_based_stop_decider_rule_based_stop_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_rule_based_stop_decider_rule_based_stop_decider
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::common::util::common_lib
  modules::planning::tasks::task
  modules::planning::tasks::deciders::decider_base
  modules::planning::tasks::deciders::lane_change_decider::lane_change_decider
)
add_library(modules::planning::tasks::deciders::rule_based_stop_decider::rule_based_stop_decider  ALIAS   modules_planning_tasks_deciders_rule_based_stop_decider_rule_based_stop_decider)

