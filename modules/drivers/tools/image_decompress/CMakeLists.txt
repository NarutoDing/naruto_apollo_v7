cmake_minimum_required(VERSION 3.16)

project(modules_drivers_tools_image_decompress)
message("${Green} [info] modules_drivers_tools_image_decompress cmakelist ${ColourReset}")

add_library(modules_drivers_tools_image_decompress_image_decompress_lib  SHARED
  image_decompress.cc
)
set_target_properties(modules_drivers_tools_image_decompress_image_decompress_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_tools_image_decompress_image_decompress_lib
  cyber::cyber
  modules::common::proto::error_code_cc_proto
  modules::common::proto::header_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  modules::drivers::tools::image_decompress::proto::config_cc_proto
  ${opencv}
)
add_library(modules::drivers::tools::image_decompress::image_decompress_lib  ALIAS   modules_drivers_tools_image_decompress_image_decompress_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libimage_decompress  SHARED
  ${virtual_cc}
)
set_target_properties(libimage_decompress  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libimage_decompress
  modules::drivers::tools::image_decompress::image_decompress_lib
)
