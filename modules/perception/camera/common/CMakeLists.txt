cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_common)
message("${Green} [info] modules_perception_camera_common cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_common_camera_frame  SHARED
  ${virtual_cc}
  camera_frame.h
)
set_target_properties(modules_perception_camera_common_camera_frame  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_common_camera_frame
  modules::perception::camera::common::data_provider
  modules::perception::base::base
)
add_library(modules::perception::camera::common::camera_frame  ALIAS   modules_perception_camera_common_camera_frame)

add_library(modules_perception_camera_common_camera_ground_plane  SHARED
  camera_ground_plane.cc
)
set_target_properties(modules_perception_camera_common_camera_ground_plane  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_common_camera_ground_plane
  modules::perception::common::i_lib::algorithm::i_sort
  modules::perception::common::i_lib::core::core
  modules::perception::common::i_lib::da::i_ransac
  modules::perception::common::i_lib::geometry::i_plane
)
add_library(modules::perception::camera::common::camera_ground_plane  ALIAS   modules_perception_camera_common_camera_ground_plane)

add_library(modules_perception_camera_common_data_provider  SHARED
  data_provider.cc
)
set_target_properties(modules_perception_camera_common_data_provider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_common_data_provider
  modules::perception::camera::common::undistortion_handler
  modules::perception::base::base
  ${npp}
)
add_library(modules::perception::camera::common::data_provider  ALIAS   modules_perception_camera_common_data_provider)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_common_global_config  SHARED
  ${virtual_cc}
  global_config.h
)
set_target_properties(modules_perception_camera_common_global_config  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::camera::common::global_config  ALIAS   modules_perception_camera_common_global_config)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_common_math_functions  SHARED
  ${virtual_cc}
  math_functions.h
)
set_target_properties(modules_perception_camera_common_math_functions  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::camera::common::math_functions  ALIAS   modules_perception_camera_common_math_functions)

add_library(modules_perception_camera_common_object_template_manager  SHARED
  object_template_manager.cc
)
set_target_properties(modules_perception_camera_common_object_template_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_common_object_template_manager
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::common::proto::object_template_meta_schema_cc_proto
  modules::perception::common::io::io_util
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::thread::thread
  ${gflags_LIBRARIES}
)
add_library(modules::perception::camera::common::object_template_manager  ALIAS   modules_perception_camera_common_object_template_manager)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_common_timer  SHARED
  ${virtual_cc}
  timer.h
)
set_target_properties(modules_perception_camera_common_timer  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::camera::common::timer  ALIAS   modules_perception_camera_common_timer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_common_twod_threed_util  SHARED
  ${virtual_cc}
  twod_threed_util.h
)
set_target_properties(modules_perception_camera_common_twod_threed_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_common_twod_threed_util
  modules::perception::common::i_lib::core::core
  modules::perception::common::i_lib::geometry::i_plane
  ${eigen}
)
add_library(modules::perception::camera::common::twod_threed_util  ALIAS   modules_perception_camera_common_twod_threed_util)

add_library(modules_perception_camera_common_undistortion_handler  SHARED
  undistortion_handler.cc
)
set_target_properties(modules_perception_camera_common_undistortion_handler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_common_undistortion_handler
  modules::perception::base::base
  modules::perception::base::blob
  modules::perception::common::sensor_manager::sensor_manager
)
add_library(modules::perception::camera::common::undistortion_handler  ALIAS   modules_perception_camera_common_undistortion_handler)

add_library(modules_perception_camera_common_util  SHARED
  util.cc
)
set_target_properties(modules_perception_camera_common_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_common_util
  modules::perception::base::base
)
add_library(modules::perception::camera::common::util  ALIAS   modules_perception_camera_common_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_common_lane_object  SHARED
  ${virtual_cc}
  lane_object.h
)
set_target_properties(modules_perception_camera_common_lane_object  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::camera::common::lane_object  ALIAS   modules_perception_camera_common_lane_object)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_common_common  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_camera_common_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_common_common
  modules::perception::camera::common::camera_frame
  modules::perception::camera::common::camera_ground_plane
  modules::perception::camera::common::data_provider
  modules::perception::camera::common::global_config
  
  modules::perception::camera::common::lane_object
  modules::perception::camera::common::math_functions
  modules::perception::camera::common::object_template_manager
  modules::perception::camera::common::timer
  modules::perception::camera::common::twod_threed_util
  modules::perception::camera::common::undistortion_handler
  modules::perception::camera::common::util
)
add_library(modules::perception::camera::common::common  ALIAS   modules_perception_camera_common_common)

