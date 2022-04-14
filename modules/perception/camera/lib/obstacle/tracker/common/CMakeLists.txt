cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_obstacle_tracker_common)
message("${Green} [info] modules_perception_camera_lib_obstacle_tracker_common cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_obstacle_tracker_common_similar  SHARED
  similar.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_common_similar  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_common_similar
  modules::perception::base::base
  modules::perception::camera::common::common
  ${eigen}
  similar_cuda
)
add_library(modules::perception::camera::lib::obstacle::tracker::common::similar  ALIAS   modules_perception_camera_lib_obstacle_tracker_common_similar)

add_library(modules_perception_camera_lib_obstacle_tracker_common_half_circle_angle  SHARED
  half_circle_angle.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_common_half_circle_angle  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_common_half_circle_angle
  modules::perception::camera::common::common
)
add_library(modules::perception::camera::lib::obstacle::tracker::common::half_circle_angle  ALIAS   modules_perception_camera_lib_obstacle_tracker_common_half_circle_angle)

add_library(modules_perception_camera_lib_obstacle_tracker_common_kalman_filter  SHARED
  kalman_filter.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_common_kalman_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_common_kalman_filter
  cyber::cyber
  ${eigen}
  modules::common::util::eigen_defs
)
add_library(modules::perception::camera::lib::obstacle::tracker::common::kalman_filter  ALIAS   modules_perception_camera_lib_obstacle_tracker_common_kalman_filter)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_obstacle_tracker_common_common  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_common_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_common_common
  modules::perception::camera::lib::obstacle::tracker::common::half_circle_angle
  modules::perception::camera::lib::obstacle::tracker::common::kalman_filter
  modules::perception::camera::lib::obstacle::tracker::common::similar
)
add_library(modules::perception::camera::lib::obstacle::tracker::common::common  ALIAS   modules_perception_camera_lib_obstacle_tracker_common_common)

cuda_add_library(modules_perception_camera_lib_obstacle_tracker_common_similar_cuda
  similar.cu
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_common_similar_cuda  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_common_similar_cuda
  cyber::cyber
  modules::perception::camera::common::camera_frame
  modules::perception::camera::common::util
  modules::perception::inference::utils::inference_gemm_lib
  ${cuda}
)
add_library(modules::perception::camera::lib::obstacle::tracker::common::similar_cuda  ALIAS   modules_perception_camera_lib_obstacle_tracker_common_similar_cuda)

