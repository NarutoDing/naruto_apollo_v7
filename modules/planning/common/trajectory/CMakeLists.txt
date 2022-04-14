cmake_minimum_required(VERSION 3.16)

project(modules_planning_common_trajectory)
message("${Green} [info] modules_planning_common_trajectory cmakelist ${ColourReset}")

add_library(modules_planning_common_trajectory_discretized_trajectory  SHARED
  discretized_trajectory.cc
)
set_target_properties(modules_planning_common_trajectory_discretized_trajectory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory_discretized_trajectory
  modules::common::math::linear_interpolation
  modules::common::proto::pnc_point_cc_proto
  modules::common::vehicle_state::proto::vehicle_state_cc_proto
  modules::planning::common::planning_context
  ${eigen}
)
add_library(modules::planning::common::trajectory::discretized_trajectory  ALIAS   modules_planning_common_trajectory_discretized_trajectory)

add_library(modules_planning_common_trajectory_publishable_trajectory  SHARED
  publishable_trajectory.cc
)
set_target_properties(modules_planning_common_trajectory_publishable_trajectory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory_publishable_trajectory
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::proto::planning_cc_proto
)
add_library(modules::planning::common::trajectory::publishable_trajectory  ALIAS   modules_planning_common_trajectory_publishable_trajectory)

