cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_traffic_light_preprocessor)
message("${Green} [info] modules_perception_camera_lib_traffic_light_preprocessor cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_traffic_light_preprocessor_multi_camera_projection  SHARED
  multi_camera_projection.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_preprocessor_multi_camera_projection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_traffic_light_preprocessor_multi_camera_projection
  modules::perception::camera::lib::traffic_light::preprocessor::pose
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::common::io::io_util
  modules::perception::common::sensor_manager::sensor_manager
)
add_library(modules::perception::camera::lib::traffic_light::preprocessor::multi_camera_projection  ALIAS   modules_perception_camera_lib_traffic_light_preprocessor_multi_camera_projection)

add_library(modules_perception_camera_lib_traffic_light_preprocessor_pose  SHARED
  pose.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_preprocessor_pose  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_traffic_light_preprocessor_pose
  cyber::cyber
  modules::common::util::eigen_defs
  modules::perception::base::base
)
add_library(modules::perception::camera::lib::traffic_light::preprocessor::pose  ALIAS   modules_perception_camera_lib_traffic_light_preprocessor_pose)

add_library(modules_perception_camera_lib_traffic_light_preprocessor_tl_preprocessor  SHARED
  tl_preprocessor.cc
)
set_target_properties(modules_perception_camera_lib_traffic_light_preprocessor_tl_preprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_traffic_light_preprocessor_tl_preprocessor
  modules::perception::camera::lib::traffic_light::preprocessor::multi_camera_projection
  modules::perception::camera::lib::traffic_light::preprocessor::pose
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::lib::interface::base_tl_preprocessor
  modules::perception::lib::registerer::registerer
  modules::perception::lib::config_manager::config_manager
  ${gflags_LIBRARIES}
  ${eigen}
  
)
add_library(modules::perception::camera::lib::traffic_light::preprocessor::tl_preprocessor  ALIAS   modules_perception_camera_lib_traffic_light_preprocessor_tl_preprocessor)

