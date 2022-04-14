cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios)
message("${Green} [info] modules_planning_scenarios cmakelist ${ColourReset}")

add_library(modules_planning_scenarios_scenario  SHARED
  scenario.cc
)
set_target_properties(modules_planning_scenarios_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_scenario
  modules::planning::scenarios::stage
  modules::planning::common::planning_common
  modules::planning::common::util::util_lib
  modules::planning::tasks::task
)
add_library(modules::planning::scenarios::scenario  ALIAS   modules_planning_scenarios_scenario)

add_library(modules_planning_scenarios_stage  SHARED
  stage.cc
)
set_target_properties(modules_planning_scenarios_stage  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_stage
  modules::planning::common::planning_common
  modules::planning::common::util::util_lib
  modules::planning::tasks::task
  modules::planning::tasks::task_factory
)
add_library(modules::planning::scenarios::stage  ALIAS   modules_planning_scenarios_stage)

add_library(modules_planning_scenarios_scenario_manager  SHARED
  scenario_manager.cc
)
set_target_properties(modules_planning_scenarios_scenario_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_scenario_manager
  modules::common::configs::vehicle_config_helper
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::common::planning_common
  modules::planning::common::planning_context
  modules::planning::common::util::util_lib
  modules::planning::scenarios::bare_intersection::unprotected::bare_intersection_unprotected_scenario
  modules::planning::scenarios::emergency::emergency_pull_over::emergency_pull_over_scenario
  modules::planning::scenarios::emergency::emergency_stop::emergency_stop_scenario
  modules::planning::scenarios::lane_follow::lane_follow
  modules::planning::scenarios::learning_model::learning_model
  modules::planning::scenarios::park::pull_over::pull_over_scenario
  modules::planning::scenarios::park::valet_parking::valet_parking
  modules::planning::scenarios::park_and_go::park_and_go_scenario
  modules::planning::scenarios::stop_sign::unprotected::stop_sign_unprotected_scenario
  modules::planning::scenarios::traffic_light::protected::traffic_light_protected_scenario
  modules::planning::scenarios::traffic_light::unprotected_left_turn::traffic_light_unprotected_left_turn_scenario
  modules::planning::scenarios::traffic_light::unprotected_right_turn::traffic_light_unprotected_right_turn_scenario
  modules::planning::scenarios::yield_sign::yield_sign_scenario
  modules::planning::scenarios::dead_end::deadend_turnaround::deadend_turnaround
)
add_library(modules::planning::scenarios::scenario_manager  ALIAS   modules_planning_scenarios_scenario_manager)

