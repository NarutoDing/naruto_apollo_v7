cmake_minimum_required(VERSION 3.16)

project(modules_planning_tasks_learning_model)
message("${Green} [info] modules_planning_tasks_learning_model cmakelist ${ColourReset}")

add_library(modules_planning_tasks_learning_model_learning_model_inference_task  SHARED
  learning_model_inference_task.cc
)
set_target_properties(modules_planning_tasks_learning_model_learning_model_inference_task  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_learning_model_learning_model_inference_task
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::reference_line_info
  modules::planning::common::trajectory_evaluator
  modules::planning::learning_based::img_feature_renderer::birdview_img_feature_renderer
  modules::planning::learning_based::model_inference::trajectory_imitation_libtorch_inference
  modules::planning::proto::learning_data_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::tasks::task
)
add_library(modules::planning::tasks::learning_model::learning_model_inference_task  ALIAS   modules_planning_tasks_learning_model_learning_model_inference_task)

add_library(modules_planning_tasks_learning_model_learning_model_inference_trajectory_task  SHARED
  learning_model_inference_trajectory_task.cc
)
set_target_properties(modules_planning_tasks_learning_model_learning_model_inference_trajectory_task  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_tasks_learning_model_learning_model_inference_trajectory_task
  modules::common::status::status
  modules::planning::common::frame
  modules::planning::common::reference_line_info
  modules::planning::proto::planning_config_cc_proto
  modules::planning::tasks::task
)
add_library(modules::planning::tasks::learning_model::learning_model_inference_trajectory_task  ALIAS   modules_planning_tasks_learning_model_learning_model_inference_trajectory_task)

