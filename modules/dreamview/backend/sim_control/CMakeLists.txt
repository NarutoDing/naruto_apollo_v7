cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_sim_control)
message("${Green} [info] modules_dreamview_backend_sim_control cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_sim_control_sim_control  SHARED
  sim_control.cc
)
set_target_properties(modules_dreamview_backend_sim_control_sim_control  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_sim_control_sim_control
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::dreamview::backend::common::dreamview_gflags
  modules::dreamview::backend::map::map_service
  modules::map::relative_map::proto::navigation_cc_proto
  modules::planning::proto::planning_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
  modules::prediction::proto::scenario_cc_proto
  
)
add_library(modules::dreamview::backend::sim_control::sim_control  ALIAS   modules_dreamview_backend_sim_control_sim_control)

