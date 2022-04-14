cmake_minimum_required(VERSION 3.16)

project(modules_drivers_video)
message("${Green} [info] modules_drivers_video cmakelist ${ColourReset}")

add_library(modules_drivers_video_video_driver_component_lib  SHARED
  video_driver_component.cc
)
set_target_properties(modules_drivers_video_video_driver_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_video_video_driver_component_lib
  cyber::cyber
  modules::common::util::message_util
  modules::drivers::video::driver
  modules::drivers::video::socket
)
add_library(modules::drivers::video::video_driver_component_lib  ALIAS   modules_drivers_video_video_driver_component_lib)

add_library(modules_drivers_video_driver  SHARED
  driver.cc
)
set_target_properties(modules_drivers_video_driver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_video_driver
  cyber::cyber
  modules::drivers::proto::sensor_image_cc_proto
  modules::drivers::video::proto::video_h265cfg_cc_proto
)
add_library(modules::drivers::video::driver  ALIAS   modules_drivers_video_driver)

add_library(modules_drivers_video_socket  SHARED
  socket_input.cc
)
set_target_properties(modules_drivers_video_socket  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_video_socket
  cyber::cyber
  modules::common::proto::error_code_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::util::util
  modules::drivers::proto::sensor_image_cc_proto
)
add_library(modules::drivers::video::socket  ALIAS   modules_drivers_video_socket)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libvideo_driver_component  SHARED
  ${virtual_cc}
)
set_target_properties(libvideo_driver_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libvideo_driver_component
  modules::drivers::video::video_driver_component_lib
)
