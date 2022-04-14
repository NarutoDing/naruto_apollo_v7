cmake_minimum_required(VERSION 3.16)

project(modules_planning_scenarios_learning_model)
message("${Green} [info] modules_planning_scenarios_learning_model cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_scenarios_learning_model_learning_model  SHARED
  ${virtual_cc}
)
set_target_properties(modules_planning_scenarios_learning_model_learning_model  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_learning_model_learning_model
  modules::planning::scenarios::learning_model::learning_model_sample_scenario
)
add_library(modules::planning::scenarios::learning_model::learning_model  ALIAS   modules_planning_scenarios_learning_model_learning_model)

add_library(modules_planning_scenarios_learning_model_learning_model_sample_scenario  SHARED
  learning_model_sample_scenario.cc
  stage_run.cc
)
set_target_properties(modules_planning_scenarios_learning_model_learning_model_sample_scenario  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_scenarios_learning_model_learning_model_sample_scenario
  cyber::common::log
  modules::common::proto::pnc_point_cc_proto
  modules::common::status::status
  modules::common::util::factory
  modules::planning::reference_line::reference_line
  modules::planning::scenarios::scenario
  ${eigen}
  
)
add_library(modules::planning::scenarios::learning_model::learning_model_sample_scenario  ALIAS   modules_planning_scenarios_learning_model_learning_model_sample_scenario)

