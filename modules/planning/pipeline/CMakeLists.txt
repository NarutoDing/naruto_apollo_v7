cmake_minimum_required(VERSION 3.16)

project(modules_planning_pipeline)
message("${Green} [info] modules_planning_pipeline cmakelist ${ColourReset}")

add_library(modules_planning_pipeline_evaluator  SHARED
  evaluator.cc
)
set_target_properties(modules_planning_pipeline_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_pipeline_evaluator
  modules::planning::pipeline::evaluator_logger
  cyber::cyber
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory_evaluator
  modules::planning::common::util::util_lib
  modules::planning::proto::learning_data_cc_proto
)
add_library(modules::planning::pipeline::evaluator  ALIAS   modules_planning_pipeline_evaluator)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_pipeline_evaluator_logger  SHARED
  ${virtual_cc}
  evaluator_logger.h
)
set_target_properties(modules_planning_pipeline_evaluator_logger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_pipeline_evaluator_logger
  cyber::cyber
  modules::planning::common::planning_gflags
)
add_library(modules::planning::pipeline::evaluator_logger  ALIAS   modules_planning_pipeline_evaluator_logger)

add_executable(evaluate_trajectory
  evaluate_trajectory.cc
)
target_link_libraries(evaluate_trajectory
  modules::planning::pipeline::evaluator
)
add_executable(record_to_learning_data
  record_to_learning_data.cc
)
target_link_libraries(record_to_learning_data
  modules::planning::common::feature_output
  modules::planning::common::message_process
  modules::planning::common::planning_gflags
)
