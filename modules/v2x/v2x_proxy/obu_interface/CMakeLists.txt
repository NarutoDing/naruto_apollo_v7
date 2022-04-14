cmake_minimum_required(VERSION 3.16)

project(modules_v2x_v2x_proxy_obu_interface)
message("${Green} [info] modules_v2x_v2x_proxy_obu_interface cmakelist ${ColourReset}")

add_library(modules_v2x_v2x_proxy_obu_interface_obu_interface_grpc_impl  SHARED
  obu_interface_grpc_impl.cc
)
set_target_properties(modules_v2x_v2x_proxy_obu_interface_obu_interface_grpc_impl  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_v2x_proxy_obu_interface_obu_interface_grpc_impl
  modules::v2x::v2x_proxy::obu_interface::grpc_interface::grpc_client
  modules::v2x::v2x_proxy::obu_interface::grpc_interface::grpc_server
  ${grpc}
)
add_library(modules::v2x::v2x_proxy::obu_interface::obu_interface_grpc_impl  ALIAS   modules_v2x_v2x_proxy_obu_interface_obu_interface_grpc_impl)

