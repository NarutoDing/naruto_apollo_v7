cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_handlers)
message("${Green} [info] modules_dreamview_backend_handlers cmakelist ${ColourReset}")

add_library(modules_dreamview_backend_handlers_websocket_handler  SHARED
  websocket_handler.cc
)
set_target_properties(modules_dreamview_backend_handlers_websocket_handler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_handlers_websocket_handler
  cyber::common::log
  modules::common::util::map_util
  ${civetweb}
  ${json}
)
add_library(modules::dreamview::backend::handlers::websocket_handler  ALIAS   modules_dreamview_backend_handlers_websocket_handler)

add_library(modules_dreamview_backend_handlers_image_handler  SHARED
  image_handler.cc
)
set_target_properties(modules_dreamview_backend_handlers_image_handler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_handlers_image_handler
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::configs::config_gflags
  modules::drivers::proto::sensor_image_cc_proto
  ${civetweb}
  ${opencv}
)
add_library(modules::dreamview::backend::handlers::image_handler  ALIAS   modules_dreamview_backend_handlers_image_handler)

