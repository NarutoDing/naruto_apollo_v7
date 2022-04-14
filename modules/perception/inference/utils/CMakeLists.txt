cmake_minimum_required(VERSION 3.16)

project(modules_perception_inference_utils)
message("${Green} [info] modules_perception_inference_utils cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_inference_utils_inference_cuda_util_lib  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_inference_utils_inference_cuda_util_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_utils_inference_cuda_util_lib
  ${tensorrt}
  ${opencv}
  inference_cuda_util_cuda_lib
)
add_library(modules::perception::inference::utils::inference_cuda_util_lib  ALIAS   modules_perception_inference_utils_inference_cuda_util_lib)

add_library(modules_perception_inference_utils_inference_util_lib  SHARED
  util.cc
)
set_target_properties(modules_perception_inference_utils_inference_util_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_utils_inference_util_lib
  modules::perception::base::blob
  modules::perception::base::box
  modules::perception::base::image
  modules::perception::base::point_cloud
  ${tensorrt}
  ${opencv}
  inference_util_cuda_lib
)
add_library(modules::perception::inference::utils::inference_util_lib  ALIAS   modules_perception_inference_utils_inference_util_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_inference_utils_inference_resize_lib  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_inference_utils_inference_resize_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_utils_inference_resize_lib
  ${tensorrt}
  ${opencv}
  inference_resize_cuda_lib
)
add_library(modules::perception::inference::utils::inference_resize_lib  ALIAS   modules_perception_inference_utils_inference_resize_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_inference_utils_inference_gemm_lib  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_inference_utils_inference_gemm_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_utils_inference_gemm_lib
  ${tensorrt}
  ${opencv}
  inference_gemm_cuda_lib
)
add_library(modules::perception::inference::utils::inference_gemm_lib  ALIAS   modules_perception_inference_utils_inference_gemm_lib)

add_library(modules_perception_inference_utils_inference_binary_data_lib  SHARED
  binary_data.cc
)
set_target_properties(modules_perception_inference_utils_inference_binary_data_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_utils_inference_binary_data_lib
  modules::perception::base::blob
  ${tensorrt}
  ${opencv}
)
add_library(modules::perception::inference::utils::inference_binary_data_lib  ALIAS   modules_perception_inference_utils_inference_binary_data_lib)

cuda_add_library(modules_perception_inference_utils_inference_cuda_util_cuda_lib
  cuda_util.cu
)
set_target_properties(modules_perception_inference_utils_inference_cuda_util_cuda_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_utils_inference_cuda_util_cuda_lib
  cyber::cyber
  ${boost}
  ${cuda}
)
add_library(modules::perception::inference::utils::inference_cuda_util_cuda_lib  ALIAS   modules_perception_inference_utils_inference_cuda_util_cuda_lib)

cuda_add_library(modules_perception_inference_utils_inference_util_cuda_lib
  util.cu
)
set_target_properties(modules_perception_inference_utils_inference_util_cuda_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_utils_inference_util_cuda_lib
  cyber::cyber
  modules::perception::base::base
  ${eigen}
  ${cuda}
)
add_library(modules::perception::inference::utils::inference_util_cuda_lib  ALIAS   modules_perception_inference_utils_inference_util_cuda_lib)

cuda_add_library(modules_perception_inference_utils_inference_resize_cuda_lib
  resize.cu
)
set_target_properties(modules_perception_inference_utils_inference_resize_cuda_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_utils_inference_resize_cuda_lib
  modules::perception::inference::utils::inference_cuda_util_lib
  modules::perception::inference::utils::inference_util_lib
  cyber::cyber
  modules::perception::base::blob
  modules::perception::base::image
  ${cuda}
)
add_library(modules::perception::inference::utils::inference_resize_cuda_lib  ALIAS   modules_perception_inference_utils_inference_resize_cuda_lib)

cuda_add_library(modules_perception_inference_utils_inference_gemm_cuda_lib
  gemm.cu
)
set_target_properties(modules_perception_inference_utils_inference_gemm_cuda_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_inference_utils_inference_gemm_cuda_lib
  modules::perception::inference::utils::inference_cuda_util_lib
  modules::perception::inference::utils::inference_util_lib
  cyber::cyber
  modules::perception::base::blob
  modules::perception::base::image
  ${cuda}
)
add_library(modules::perception::inference::utils::inference_gemm_cuda_lib  ALIAS   modules_perception_inference_utils_inference_gemm_cuda_lib)

