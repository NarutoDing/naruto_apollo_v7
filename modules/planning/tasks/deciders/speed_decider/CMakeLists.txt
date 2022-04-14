cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_deciders_speed_decider)
message("${Green} [info] modules_planning_tasks_deciders_speed_decider cmakelist ${ColourReset}")

add_library(modules_planning_tasks_deciders_speed_decider_speed_decider  SHARED
  speed_decider.cc
)
set_target_properties(modules_planning_tasks_deciders_speed_decider_speed_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_deciders_speed_decider_speed_decider
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::path_decision
  modules::planning::common::planning_gflags
  modules::planning::common::reference_line_info
  modules::planning::proto::planning_cc_proto
  modules::planning::tasks::task
  modules::planning::tasks::utils::st_gap_estimator
)
add_library(modules::planning::tasks::deciders::speed_decider::speed_decider  ALIAS   modules_planning_tasks_deciders_speed_decider_speed_decider)

