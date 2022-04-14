cmake_minimum_required(VERSION 3.16)

project(modules_v2x_v2x_proxy_app)
message("${Green} [info] modules_v2x_v2x_proxy_app cmakelist ${ColourReset}")

add_library(modules_v2x_v2x_proxy_app_utils  SHARED
  utils.cc
)
set_target_properties(modules_v2x_v2x_proxy_app_utils  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_v2x_proxy_app_utils
  cyber::cyber
  modules::common::math::quaternion
  modules::map::hdmap::hdmap_util
  modules::v2x::v2x_proxy::obu_interface::obu_interface_grpc_impl
  modules::v2x::v2x_proxy::os_interface::os_interface
  modules::v2x::v2x_proxy::proto_adapter::proto_adapter
)
add_library(modules::v2x::v2x_proxy::app::utils  ALIAS   modules_v2x_v2x_proxy_app_utils)

add_library(modules_v2x_v2x_proxy_app_v2x_proxy  SHARED
  v2x_proxy.cc
)
set_target_properties(modules_v2x_v2x_proxy_app_v2x_proxy  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_v2x_proxy_app_v2x_proxy
  modules::v2x::v2x_proxy::app::utils
  cyber::cyber
  modules::map::hdmap::hdmap_util
  modules::v2x::v2x_proxy::obu_interface::obu_interface_grpc_impl
  modules::v2x::v2x_proxy::os_interface::os_interface
  modules::v2x::v2x_proxy::proto_adapter::proto_adapter
)
add_library(modules::v2x::v2x_proxy::app::v2x_proxy  ALIAS   modules_v2x_v2x_proxy_app_v2x_proxy)

add_executable(v2x
  main.cc
)
target_link_libraries(v2x
  modules::v2x::v2x_proxy::app::v2x_proxy
)
