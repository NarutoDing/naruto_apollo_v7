cmake_minimum_required(VERSION 3.16)

project(modules_drivers_smartereye)
message("${Green} [info] modules_drivers_smartereye cmakelist ${ColourReset}")

add_library(modules_drivers_smartereye_smartereye_component_lib  SHARED
  smartereye_component.cc
)
set_target_properties(modules_drivers_smartereye_smartereye_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_smartereye_smartereye_component_lib
  modules::drivers::smartereye::smartereye_device
  modules::drivers::smartereye::smartereye_handler
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::proto::error_code_cc_proto
  modules::common::proto::header_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  modules::drivers::proto::smartereye_cc_proto
  third_party::camera_library::smartereye::smartereye
)
add_library(modules::drivers::smartereye::smartereye_component_lib  ALIAS   modules_drivers_smartereye_smartereye_component_lib)

add_library(modules_drivers_smartereye_smartereye_device  SHARED
  smartereye_device.cc
)
set_target_properties(modules_drivers_smartereye_smartereye_device  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_smartereye_smartereye_device
  modules::drivers::smartereye::smartereye_handler
  cyber::cyber
  modules::drivers::smartereye::proto::config_cc_proto
  third_party::camera_library::smartereye::smartereye
)
add_library(modules::drivers::smartereye::smartereye_device  ALIAS   modules_drivers_smartereye_smartereye_device)

add_library(modules_drivers_smartereye_smartereye_handler  SHARED
  smartereye_handler.cc
)
set_target_properties(modules_drivers_smartereye_smartereye_handler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_smartereye_smartereye_handler
  cyber::cyber
  third_party::camera_library::smartereye::smartereye
)
add_library(modules::drivers::smartereye::smartereye_handler  ALIAS   modules_drivers_smartereye_smartereye_handler)

add_library(modules_drivers_smartereye_compress_component_lib  SHARED
  compress_component.cc
)
set_target_properties(modules_drivers_smartereye_compress_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_smartereye_compress_component_lib
  cyber::cyber
  modules::common::proto::error_code_cc_proto
  modules::common::proto::header_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  modules::drivers::proto::smartereye_cc_proto
  modules::drivers::smartereye::proto::config_cc_proto
  ${opencv}
)
add_library(modules::drivers::smartereye::compress_component_lib  ALIAS   modules_drivers_smartereye_compress_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libsmartereye_component  SHARED
  ${virtual_cc}
)
set_target_properties(libsmartereye_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libsmartereye_component
  modules::drivers::smartereye::compress_component_lib
  modules::drivers::smartereye::smartereye_component_lib
)
