cmake_minimum_required(VERSION 3.16)

project(modules_planning_common_path)
message("${Green} [info] modules_planning_common_path cmakelist ${ColourReset}")

add_library(modules_planning_common_path_discretized_path  SHARED
  discretized_path.cc
)
set_target_properties(modules_planning_common_path_discretized_path  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_path_discretized_path
  modules::common::math::linear_interpolation
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::planning::common::path::discretized_path  ALIAS   modules_planning_common_path_discretized_path)

add_library(modules_planning_common_path_frenet_frame_path  SHARED
  frenet_frame_path.cc
)
set_target_properties(modules_planning_common_path_frenet_frame_path  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_path_frenet_frame_path
  modules::common::math::linear_interpolation
  modules::planning::proto::planning_cc_proto
)
add_library(modules::planning::common::path::frenet_frame_path  ALIAS   modules_planning_common_path_frenet_frame_path)

add_library(modules_planning_common_path_path_data  SHARED
  path_data.cc
)
set_target_properties(modules_planning_common_path_path_data  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_path_path_data
  modules::planning::common::path::discretized_path
  modules::planning::common::path::frenet_frame_path
  modules::common::math::cartesian_frenet_conversion
  modules::planning::common::planning_gflags
  modules::planning::reference_line::reference_line
)
add_library(modules::planning::common::path::path_data  ALIAS   modules_planning_common_path_path_data)

