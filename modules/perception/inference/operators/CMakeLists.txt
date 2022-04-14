cmake_minimum_required(VERSION 3.16)

project(modules_perception_inference_operators)
message("${Green} [info] modules_perception_inference_operators cmakelist ${ColourReset}")

add_library(modules_perception_inference_operators_perception_inference_operators  SHARED
  roipooling_layer.cc
)
set_target_properties(modules_perception_inference_operators_perception_inference_operators  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_operators_perception_inference_operators
  modules::perception::base::blob
  modules::perception::inference::layer_lib
  perception_inference_operators_cuda
)
add_library(modules::perception::inference::operators::perception_inference_operators  ALIAS   modules_perception_inference_operators_perception_inference_operators)

cuda_add_library(modules_perception_inference_operators_perception_inference_operators_cuda
  roipooling_layer.cu
)
set_target_properties(modules_perception_inference_operators_perception_inference_operators_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_operators_perception_inference_operators_cuda
  modules::perception::base::blob
  modules::perception::inference::layer_lib
  ${eigen}
  ${cuda}
)
add_library(modules::perception::inference::operators::perception_inference_operators_cuda  ALIAS   modules_perception_inference_operators_perception_inference_operators_cuda)

