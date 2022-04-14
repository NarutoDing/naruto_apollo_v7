cmake_minimum_required(VERSION 3.16)

project(modules_perception_inference_tools)
message("${Green} [info] modules_perception_inference_tools cmakelist ${ColourReset}")

add_executable(cal_table_generator
  cal_table_generator.cc
)
target_link_libraries(cal_table_generator
  modules::perception::inference::inference_lib
  modules::perception::inference::tensorrt::batch_stream
  modules::perception::inference::tensorrt::entropy_calibrator
  modules::perception::inference::tensorrt::rt_net
  modules::perception::inference::utils::inference_util_lib
)
add_executable(denseline_sample
  denseline_sample.cc
)
target_link_libraries(denseline_sample
  modules::perception::inference::inference_lib
  modules::perception::inference::tensorrt::batch_stream
  modules::perception::inference::tensorrt::entropy_calibrator
  modules::perception::inference::tensorrt::rt_net
  modules::perception::inference::utils::inference_util_lib
)
add_executable(lane_sample
  lane_sample.cc
)
target_link_libraries(lane_sample
  modules::perception::inference::inference_lib
  modules::perception::inference::tensorrt::batch_stream
  modules::perception::inference::tensorrt::entropy_calibrator
  modules::perception::inference::tensorrt::rt_net
  modules::perception::inference::utils::inference_util_lib
)
add_executable(yolo_sample
  yolo_sample.cc
)
target_link_libraries(yolo_sample
  modules::perception::inference::inference_lib
  modules::perception::inference::tensorrt::batch_stream
  modules::perception::inference::tensorrt::entropy_calibrator
  modules::perception::inference::tensorrt::rt_net
  modules::perception::inference::utils::inference_util_lib
)
