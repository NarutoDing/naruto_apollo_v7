cmake_minimum_required(VERSION 3.16)

project(modules_perception_inference_tensorrt)
message("${Green} [info] modules_perception_inference_tensorrt cmakelist ${ColourReset}")

add_library(modules_perception_inference_tensorrt_rt_common  SHARED
  rt_common.cc
)
set_target_properties(modules_perception_inference_tensorrt_rt_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_rt_common
  cyber::cyber
  modules::perception::base::common
  modules::perception::proto::rt_cc_proto
  ${absl}
  ${cuda}
)
add_library(modules::perception::inference::tensorrt::rt_common  ALIAS   modules_perception_inference_tensorrt_rt_common)

add_library(modules_perception_inference_tensorrt_rt_utils  SHARED
  rt_utils.cc
)
set_target_properties(modules_perception_inference_tensorrt_rt_utils  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_rt_utils
  cyber::cyber
  modules::perception::proto::rt_cc_proto
  ${tensorrt}
)
add_library(modules::perception::inference::tensorrt::rt_utils  ALIAS   modules_perception_inference_tensorrt_rt_utils)

add_library(modules_perception_inference_tensorrt_rt_net  SHARED
  rt_net.cc
)
set_target_properties(modules_perception_inference_tensorrt_rt_net  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_rt_net
  modules::perception::inference::tensorrt::batch_stream
  modules::perception::inference::tensorrt::entropy_calibrator
  modules::perception::inference::tensorrt::rt_common
  modules::perception::inference::tensorrt::rt_utils
  cyber::cyber
  modules::perception::base::base
  modules::perception::inference::inference_lib
  modules::perception::inference::tensorrt::plugins::perception_inference_tensorrt_plugins
  ${Protobuf_LIBRARIES}
  ${tensorrt}
  ${opencv}
)
add_library(modules::perception::inference::tensorrt::rt_net  ALIAS   modules_perception_inference_tensorrt_rt_net)

add_library(modules_perception_inference_tensorrt_entropy_calibrator  SHARED
  entropy_calibrator.cc
)
set_target_properties(modules_perception_inference_tensorrt_entropy_calibrator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_entropy_calibrator
  modules::perception::inference::tensorrt::batch_stream
  modules::perception::inference::tensorrt::rt_utils
  ${Protobuf_LIBRARIES}
  ${cuda}
  ${tensorrt}
  ${opencv}
)
add_library(modules::perception::inference::tensorrt::entropy_calibrator  ALIAS   modules_perception_inference_tensorrt_entropy_calibrator)

add_library(modules_perception_inference_tensorrt_batch_stream  SHARED
  batch_stream.cc
)
set_target_properties(modules_perception_inference_tensorrt_batch_stream  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_batch_stream
  cyber::cyber
  modules::perception::proto::rt_cc_proto
  ${absl}
  ${Protobuf_LIBRARIES}
  ${opencv}
)
add_library(modules::perception::inference::tensorrt::batch_stream  ALIAS   modules_perception_inference_tensorrt_batch_stream)

