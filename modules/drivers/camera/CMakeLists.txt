cmake_minimum_required(VERSION 3.16)

project(modules_drivers_camera)
message("${Green} [info] modules_drivers_camera cmakelist ${ColourReset}")

add_library(modules_drivers_camera_camera_component_lib  SHARED
  camera_component.cc
)
set_target_properties(modules_drivers_camera_camera_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_camera_camera_component_lib
  modules::drivers::camera::camera
  cyber::cyber
  modules::common::proto::error_code_cc_proto
  modules::common::proto::header_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
)
add_library(modules::drivers::camera::camera_component_lib  ALIAS   modules_drivers_camera_camera_component_lib)

add_library(modules_drivers_camera_compress_component_lib  SHARED
  compress_component.cc
)
set_target_properties(modules_drivers_camera_compress_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_camera_compress_component_lib
  cyber::cyber
  modules::common::proto::error_code_cc_proto
  modules::common::proto::header_cc_proto
  modules::drivers::camera::proto::config_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  ${opencv}
)
add_library(modules::drivers::camera::compress_component_lib  ALIAS   modules_drivers_camera_compress_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_drivers_camera_camera  SHARED
  ${virtual_cc}
)
set_target_properties(modules_drivers_camera_camera  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::camera::camera  ALIAS   modules_drivers_camera_camera)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libcamera_component  SHARED
  ${virtual_cc}
)
set_target_properties(libcamera_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libcamera_component
  modules::drivers::camera::camera_component_lib
  modules::drivers::camera::compress_component_lib
  ${ffmpeg}
)
