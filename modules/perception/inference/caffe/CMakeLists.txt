cmake_minimum_required(VERSION 3.16)

project(modules_perception_inference_caffe)
message("${Green} [info] modules_perception_inference_caffe cmakelist ${ColourReset}")

add_library(modules_perception_inference_caffe_caffe_net_lib  SHARED
  caffe_net.cc
)
set_target_properties(modules_perception_inference_caffe_caffe_net_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_caffe_caffe_net_lib
  modules::perception::inference::inference_lib
  ${boost}
  ${caffe}
  ${Protobuf_LIBRARIES}
  ${tensorrt}
  ${opencv}
)
add_library(modules::perception::inference::caffe::caffe_net_lib  ALIAS   modules_perception_inference_caffe_caffe_net_lib)

