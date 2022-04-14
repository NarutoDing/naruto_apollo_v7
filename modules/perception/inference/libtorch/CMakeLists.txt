cmake_minimum_required(VERSION 3.16)

project(modules_perception_inference_libtorch)
message("${Green} [info] modules_perception_inference_libtorch cmakelist ${ColourReset}")

add_library(modules_perception_inference_libtorch_torch_net  SHARED
  torch_net.cc
)
set_target_properties(modules_perception_inference_libtorch_torch_net  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_libtorch_torch_net
  modules::perception::inference::inference_lib
  ${libtorch}
  ${Protobuf_LIBRARIES}
  ${opencv}
  ${cuda}
)
add_library(modules::perception::inference::libtorch::torch_net  ALIAS   modules_perception_inference_libtorch_torch_net)

add_library(modules_perception_inference_libtorch_torch_det  SHARED
  torch_det.cc
)
set_target_properties(modules_perception_inference_libtorch_torch_det  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_libtorch_torch_det
  modules::perception::inference::inference_lib
  ${libtorch}
  ${Protobuf_LIBRARIES}
  ${opencv}
  ${cuda}
)
add_library(modules::perception::inference::libtorch::torch_det  ALIAS   modules_perception_inference_libtorch_torch_det)

