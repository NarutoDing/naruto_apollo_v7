cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_rss_decider)
message("${Green} [info] modules_planning_tasks_deciders_rss_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_rss_decider_rss_decider  SHARED
  rss_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_rss_decider_rss_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_rss_decider_rss_decider
  modules::common::status::status
  modules::planning::common::planning_context
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::proto::planning_cc_proto
  modules::planning::tasks::task
  ${ad_rss}
)
add_library(modules::planning::tasks::deciders::rss_decider::rss_decider  ALIAS   modules_planning_tasks_deciders_rss_decider_rss_decider)

