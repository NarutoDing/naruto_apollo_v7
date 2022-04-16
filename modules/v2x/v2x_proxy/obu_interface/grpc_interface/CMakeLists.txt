cmake_minimum_required(VERSION 3.16)

project(modules_v2x_v2x_proxy_obu_interface_grpc_interface)
message("${Green} [info] modules_v2x_v2x_proxy_obu_interface_grpc_interface cmakelist ${ColourReset}")

add_library(modules_v2x_v2x_proxy_obu_interface_grpc_interface_grpc_client  SHARED
  grpc_client.cc
)
set_target_properties(modules_v2x_v2x_proxy_obu_interface_grpc_interface_grpc_client  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_v2x_proxy_obu_interface_grpc_interface_grpc_client
  cyber::cyber
  modules::v2x::common::v2x_proxy_gflags
  modules::v2x::proto::v2x_service_car_to_obu_cc_proto
  modules::v2x::proto::v2x_service_obu_to_car_cc_proto
  ${grpc}
)
add_library(modules::v2x::v2x_proxy::obu_interface::grpc_interface::grpc_client  ALIAS   modules_v2x_v2x_proxy_obu_interface_grpc_interface_grpc_client)

add_library(modules_v2x_v2x_proxy_obu_interface_grpc_interface_grpc_server  SHARED
  grpc_server.cc
)
set_target_properties(modules_v2x_v2x_proxy_obu_interface_grpc_interface_grpc_server  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_v2x_proxy_obu_interface_grpc_interface_grpc_server
  cyber::cyber
  modules::perception::proto::perception_obstacle_cc_proto
  modules::perception::proto::traffic_light_detection_cc_proto
  modules::v2x::common::v2x_proxy_gflags
  modules::v2x::proto::v2x_obu_rsi_cc_proto
  modules::v2x::proto::v2x_service_car_to_obu_cc_proto
  modules::v2x::proto::v2x_service_obu_to_car_cc_proto
  modules::v2x::proto::v2x_traffic_light_cc_proto
  ${grpc}
)
add_library(modules::v2x::v2x_proxy::obu_interface::grpc_interface::grpc_server  ALIAS   modules_v2x_v2x_proxy_obu_interface_grpc_interface_grpc_server)

