cmake_minimum_required(VERSION 3.16)

project(modules_perception_inference_tensorrt_plugins)
message("${Green} [info] modules_perception_inference_tensorrt_plugins cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins
  ${cuda}
  
  dfmb_psroi_align_plugin
  kernels_cuda
  rcnn_proposal_plugin
  rpn_proposal_ssd_plugin
  perception_inference_tensorrt_plugins_argmax_cuda
  perception_inference_tensorrt_plugins_leakyrelu_cuda
  perception_inference_tensorrt_plugins_slice_cuda
  perception_inference_tensorrt_plugins_softmax_cuda
)
add_library(modules::perception::inference::tensorrt::plugins::perception_inference_tensorrt_plugins  ALIAS   modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins)

cuda_add_library(modules_perception_inference_tensorrt_plugins_kernels_cuda
  kernels.cu
  nms_cuda.cu
)
set_target_properties(modules_perception_inference_tensorrt_plugins_kernels_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_plugins_kernels_cuda
  modules::perception::base::common
  ${cuda}
)
add_library(modules::perception::inference::tensorrt::plugins::kernels_cuda  ALIAS   modules_perception_inference_tensorrt_plugins_kernels_cuda)

cuda_add_library(modules_perception_inference_tensorrt_plugins_dfmb_psroi_align_plugin
  dfmb_psroi_align_plugin.cu
)
set_target_properties(modules_perception_inference_tensorrt_plugins_dfmb_psroi_align_plugin  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_plugins_dfmb_psroi_align_plugin
  modules::perception::inference::tensorrt::plugins::kernels_cuda
  cyber::common::log
  modules::perception::inference::tensorrt::rt_common
  ${cuda}
  ${tensorrt}
)
add_library(modules::perception::inference::tensorrt::plugins::dfmb_psroi_align_plugin  ALIAS   modules_perception_inference_tensorrt_plugins_dfmb_psroi_align_plugin)

cuda_add_library(modules_perception_inference_tensorrt_plugins_rcnn_proposal_plugin
  rcnn_proposal_plugin.cu
)
set_target_properties(modules_perception_inference_tensorrt_plugins_rcnn_proposal_plugin  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_plugins_rcnn_proposal_plugin
  modules::perception::inference::tensorrt::plugins::kernels_cuda
  modules::perception::inference::tensorrt::rt_common
  ${cuda}
  ${tensorrt}
)
add_library(modules::perception::inference::tensorrt::plugins::rcnn_proposal_plugin  ALIAS   modules_perception_inference_tensorrt_plugins_rcnn_proposal_plugin)

cuda_add_library(modules_perception_inference_tensorrt_plugins_rpn_proposal_ssd_plugin
  rpn_proposal_ssd_plugin.cu
)
set_target_properties(modules_perception_inference_tensorrt_plugins_rpn_proposal_ssd_plugin  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_plugins_rpn_proposal_ssd_plugin
  modules::perception::inference::tensorrt::plugins::kernels_cuda
  modules::perception::inference::tensorrt::rt_common
  ${cuda}
  ${tensorrt}
)
add_library(modules::perception::inference::tensorrt::plugins::rpn_proposal_ssd_plugin  ALIAS   modules_perception_inference_tensorrt_plugins_rpn_proposal_ssd_plugin)

cuda_add_library(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_slice_cuda
  slice_plugin.cu
)
set_target_properties(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_slice_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_slice_cuda
  modules::perception::inference::tensorrt::rt_common
  ${eigen}
  ${cuda}
  ${tensorrt}
)
add_library(modules::perception::inference::tensorrt::plugins::perception_inference_tensorrt_plugins_slice_cuda  ALIAS   modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_slice_cuda)

cuda_add_library(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_argmax_cuda
  argmax_plugin.cu
)
set_target_properties(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_argmax_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_argmax_cuda
  modules::perception::inference::tensorrt::rt_common
  ${eigen}
  ${cuda}
  ${tensorrt}
)
add_library(modules::perception::inference::tensorrt::plugins::perception_inference_tensorrt_plugins_argmax_cuda  ALIAS   modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_argmax_cuda)

cuda_add_library(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_softmax_cuda
  softmax_plugin.cu
)
set_target_properties(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_softmax_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_softmax_cuda
  modules::perception::inference::tensorrt::rt_common
  ${eigen}
  ${cuda}
  ${tensorrt}
)
add_library(modules::perception::inference::tensorrt::plugins::perception_inference_tensorrt_plugins_softmax_cuda  ALIAS   modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_softmax_cuda)

cuda_add_library(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_leakyrelu_cuda
  leakyReLU_plugin.cu
)
set_target_properties(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_leakyrelu_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_leakyrelu_cuda
  modules::perception::inference::tensorrt::rt_common
  ${eigen}
  ${cuda}
  ${tensorrt}
)
add_library(modules::perception::inference::tensorrt::plugins::perception_inference_tensorrt_plugins_leakyrelu_cuda  ALIAS   modules_perception_inference_tensorrt_plugins_perception_inference_tensorrt_plugins_leakyrelu_cuda)

