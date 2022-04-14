cmake_minimum_required(VERSION 3.16)

project(modules_prediction_evaluator_pedestrian)
message("${Green} [info] modules_prediction_evaluator_pedestrian cmakelist ${ColourReset}")

add_library(modules_prediction_evaluator_pedestrian_pedestrian_interaction_evaluator  SHARED
  pedestrian_interaction_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_pedestrian_pedestrian_interaction_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_pedestrian_pedestrian_interaction_evaluator
  modules::prediction::container::container_manager
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  ${libtorch}
)
add_library(modules::prediction::evaluator::pedestrian::pedestrian_interaction_evaluator  ALIAS   modules_prediction_evaluator_pedestrian_pedestrian_interaction_evaluator)

