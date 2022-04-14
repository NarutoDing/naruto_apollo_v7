cmake_minimum_required(VERSION 3.16)

project(modules_perception_inference_onnx)
message("${Green} [info] modules_perception_inference_onnx cmakelist ${ColourReset}")

add_library(modules_perception_inference_onnx_onnx_obstacle_detector  SHARED
  onnx_obstacle_detector.cc
)
set_target_properties(modules_perception_inference_onnx_onnx_obstacle_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_onnx_onnx_obstacle_detector
  modules::perception::common::perception_gflags
  modules::perception::inference::inference_lib
  ${cuda}
  ${tensorrt}
)
add_library(modules::perception::inference::onnx::onnx_obstacle_detector  ALIAS   modules_perception_inference_onnx_onnx_obstacle_detector)

add_library(modules_perception_inference_onnx_libtorch_obstacle_detector  SHARED
  libtorch_obstacle_detector.cc
)
set_target_properties(modules_perception_inference_onnx_libtorch_obstacle_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_onnx_libtorch_obstacle_detector
  cyber::common::log
  modules::perception::common::perception_gflags
  modules::perception::inference::inference_lib
  ${libtorch}
)
add_library(modules::perception::inference::onnx::libtorch_obstacle_detector  ALIAS   modules_perception_inference_onnx_libtorch_obstacle_detector)

