cmake_minimum_required(VERSION 3.16)

project(modules_perception_inference)
message("${Green} [info] modules_perception_inference cmakelist ${ColourReset}")

add_library(modules_perception_inference_layer_lib  SHARED
  layer.cc
)
set_target_properties(modules_perception_inference_layer_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_layer_lib
  modules::perception::base::blob
)
add_library(modules::perception::inference::layer_lib  ALIAS   modules_perception_inference_layer_lib)

add_library(modules_perception_inference_inference_lib  SHARED
  inference.cc
)
set_target_properties(modules_perception_inference_inference_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_inference_lib
  modules::perception::base::blob
  ${boost}
)
add_library(modules::perception::inference::inference_lib  ALIAS   modules_perception_inference_inference_lib)

add_library(modules_perception_inference_inference_factory  SHARED
  inference_factory.cc
)
set_target_properties(modules_perception_inference_inference_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_inference_factory
  modules::perception::inference::inference_lib
  modules::perception::inference::libtorch::torch_det
  modules::perception::inference::libtorch::torch_net
  modules::perception::inference::onnx::libtorch_obstacle_detector
  modules::perception::inference::tensorrt::rt_net
  modules::perception::inference::utils::inference_util_lib
)
add_library(modules::perception::inference::inference_factory  ALIAS   modules_perception_inference_inference_factory)

