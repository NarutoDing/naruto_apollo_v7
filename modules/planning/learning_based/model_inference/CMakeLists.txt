cmake_minimum_required(VERSION 3.16)

project(modules_planning_learning_based_model_inference)
message("${Green} [info] modules_planning_learning_based_model_inference cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_learning_based_model_inference_model_inference  SHARED
  ${virtual_cc}
  model_inference.h
)
set_target_properties(modules_planning_learning_based_model_inference_model_inference  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_learning_based_model_inference_model_inference
  modules::planning::proto::learning_data_cc_proto
  modules::planning::proto::task_config_cc_proto
)
add_library(modules::planning::learning_based::model_inference::model_inference  ALIAS   modules_planning_learning_based_model_inference_model_inference)

add_library(modules_planning_learning_based_model_inference_trajectory_imitation_libtorch_inference  SHARED
  trajectory_imitation_libtorch_inference.cc
)
set_target_properties(modules_planning_learning_based_model_inference_trajectory_imitation_libtorch_inference  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_learning_based_model_inference_trajectory_imitation_libtorch_inference
  modules::planning::learning_based::model_inference::model_inference
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::util::math_util_lib
  modules::planning::learning_based::img_feature_renderer::birdview_img_feature_renderer
  ${libtorch}
  ${opencv}
)
add_library(modules::planning::learning_based::model_inference::trajectory_imitation_libtorch_inference  ALIAS   modules_planning_learning_based_model_inference_trajectory_imitation_libtorch_inference)

