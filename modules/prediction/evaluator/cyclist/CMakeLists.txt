cmake_minimum_required(VERSION 3.16)

project(modules_prediction_evaluator_cyclist)
message("${Green} [info] modules_prediction_evaluator_cyclist cmakelist ${ColourReset}")

add_library(modules_prediction_evaluator_cyclist_cyclist_keep_lane_evaluator  SHARED
  cyclist_keep_lane_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_cyclist_cyclist_keep_lane_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_cyclist_cyclist_keep_lane_evaluator
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
)
add_library(modules::prediction::evaluator::cyclist::cyclist_keep_lane_evaluator  ALIAS   modules_prediction_evaluator_cyclist_cyclist_keep_lane_evaluator)

