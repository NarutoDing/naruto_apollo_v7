cmake_minimum_required(VERSION 3.16)

project(modules_planning_open_space_coarse_trajectory_generator)
message("${Green} [info] modules_planning_open_space_coarse_trajectory_generator cmakelist ${ColourReset}")

add_library(modules_planning_open_space_coarse_trajectory_generator_node3d  SHARED
  node3d.cc
)
set_target_properties(modules_planning_open_space_coarse_trajectory_generator_node3d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_coarse_trajectory_generator_node3d
  cyber::common::log
  modules::common::math::math
  modules::planning::common::obstacle
  modules::planning::constraint_checker::collision_checker
  modules::planning::proto::planner_open_space_config_cc_proto
)
add_library(modules::planning::open_space::coarse_trajectory_generator::node3d  ALIAS   modules_planning_open_space_coarse_trajectory_generator_node3d)

add_library(modules_planning_open_space_coarse_trajectory_generator_reeds_shepp_path  SHARED
  reeds_shepp_path.cc
)
set_target_properties(modules_planning_open_space_coarse_trajectory_generator_reeds_shepp_path  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_coarse_trajectory_generator_reeds_shepp_path
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::planning::common::planning_gflags
  modules::planning::open_space::coarse_trajectory_generator::node3d
  modules::planning::proto::planner_open_space_config_cc_proto
  ${adolc}
)
add_library(modules::planning::open_space::coarse_trajectory_generator::reeds_shepp_path  ALIAS   modules_planning_open_space_coarse_trajectory_generator_reeds_shepp_path)

add_library(modules_planning_open_space_coarse_trajectory_generator_grid_search  SHARED
  grid_search.cc
)
set_target_properties(modules_planning_open_space_coarse_trajectory_generator_grid_search  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_coarse_trajectory_generator_grid_search
  cyber::common::log
  modules::common::math::math
  modules::planning::proto::planner_open_space_config_cc_proto
)
add_library(modules::planning::open_space::coarse_trajectory_generator::grid_search  ALIAS   modules_planning_open_space_coarse_trajectory_generator_grid_search)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_open_space_coarse_trajectory_generator_open_space_utils  SHARED
  ${virtual_cc}
)
set_target_properties(modules_planning_open_space_coarse_trajectory_generator_open_space_utils  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_coarse_trajectory_generator_open_space_utils
  modules::planning::open_space::coarse_trajectory_generator::grid_search
  modules::planning::open_space::coarse_trajectory_generator::node3d
  modules::planning::open_space::coarse_trajectory_generator::reeds_shepp_path
)
add_library(modules::planning::open_space::coarse_trajectory_generator::open_space_utils  ALIAS   modules_planning_open_space_coarse_trajectory_generator_open_space_utils)

add_library(modules_planning_open_space_coarse_trajectory_generator_hybrid_a_star  SHARED
  hybrid_a_star.cc
)
set_target_properties(modules_planning_open_space_coarse_trajectory_generator_hybrid_a_star  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_coarse_trajectory_generator_hybrid_a_star
  modules::planning::open_space::coarse_trajectory_generator::open_space_utils
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::planning::common::obstacle
  modules::planning::common::planning_gflags
  modules::planning::math::piecewise_jerk::piecewise_jerk_speed_problem
  modules::planning::proto::planner_open_space_config_cc_proto
)
add_library(modules::planning::open_space::coarse_trajectory_generator::hybrid_a_star  ALIAS   modules_planning_open_space_coarse_trajectory_generator_hybrid_a_star)

