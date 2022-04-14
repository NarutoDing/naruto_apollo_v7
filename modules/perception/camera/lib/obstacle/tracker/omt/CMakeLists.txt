cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_obstacle_tracker_omt)
message("${Green} [info] modules_perception_camera_lib_obstacle_tracker_omt cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_obstacle_tracker_omt_track_object  SHARED
  track_object.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_omt_track_object  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_omt_track_object
  modules::perception::camera::lib::obstacle::tracker::omt::frame_list
  modules::perception::base::base
  modules::perception::inference::utils::inference_cuda_util_lib
  modules::perception::inference::utils::inference_util_lib
)
add_library(modules::perception::camera::lib::obstacle::tracker::omt::track_object  ALIAS   modules_perception_camera_lib_obstacle_tracker_omt_track_object)

add_library(modules_perception_camera_lib_obstacle_tracker_omt_target  SHARED
  target.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_omt_target  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_omt_target
  modules::perception::camera::lib::obstacle::tracker::omt::frame_list
  modules::perception::camera::lib::obstacle::tracker::omt::track_object
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::obstacle::tracker::common::common
  modules::perception::camera::lib::obstacle::tracker::omt::proto::omt_cc_proto
)
add_library(modules::perception::camera::lib::obstacle::tracker::omt::target  ALIAS   modules_perception_camera_lib_obstacle_tracker_omt_target)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_obstacle_tracker_omt_frame_list  SHARED
  ${virtual_cc}
  frame_list.h
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_omt_frame_list  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_omt_frame_list
  cyber::cyber
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::inference::utils::inference_cuda_util_lib
  modules::perception::inference::utils::inference_util_lib
)
add_library(modules::perception::camera::lib::obstacle::tracker::omt::frame_list  ALIAS   modules_perception_camera_lib_obstacle_tracker_omt_frame_list)

add_library(modules_perception_camera_lib_obstacle_tracker_omt_omt_obstacle_tracker  SHARED
  omt_obstacle_tracker.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_omt_omt_obstacle_tracker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_omt_omt_obstacle_tracker
  modules::perception::camera::lib::obstacle::tracker::omt::frame_list
  modules::perception::camera::lib::obstacle::tracker::omt::obstacle_reference
  modules::perception::camera::lib::obstacle::tracker::omt::target
  cyber::common::file
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::obstacle::tracker::common::common
  modules::perception::camera::lib::obstacle::tracker::omt::proto::omt_cc_proto
  
)
add_library(modules::perception::camera::lib::obstacle::tracker::omt::omt_obstacle_tracker  ALIAS   modules_perception_camera_lib_obstacle_tracker_omt_omt_obstacle_tracker)

add_library(modules_perception_camera_lib_obstacle_tracker_omt_obstacle_reference  SHARED
  obstacle_reference.cc
)
set_target_properties(modules_perception_camera_lib_obstacle_tracker_omt_obstacle_reference  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_obstacle_tracker_omt_obstacle_reference
  modules::perception::camera::lib::obstacle::tracker::omt::frame_list
  modules::perception::camera::lib::obstacle::tracker::omt::target
  cyber::cyber
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::obstacle::tracker::omt::proto::omt_cc_proto
)
add_library(modules::perception::camera::lib::obstacle::tracker::omt::obstacle_reference  ALIAS   modules_perception_camera_lib_obstacle_tracker_omt_obstacle_reference)

