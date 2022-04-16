cmake_minimum_required(VERSION 3.16)
#ding bug
project(modules_v2x_v2x_proxy_proto_adapter)
add_library(modules_v2x_v2x_proxy_proto_adapter_proto_adapter  SHARED
  proto_adapter.cc
)
set_target_properties(modules_v2x_v2x_proxy_proto_adapter_proto_adapter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_v2x_proxy_proto_adapter_proto_adapter
  cyber::cyber
  modules::map::hdmap
  modules::v2x::common::v2x_proxy_gflags
  modules::v2x::proto::v2x_car_status_cc_proto
  modules::v2x::proto::v2x_junction_cc_proto
  modules::v2x::proto::v2x_obu_rsi_cc_proto
  modules::v2x::proto::v2x_obu_traffic_light_cc_proto
  modules::v2x::proto::v2x_rsi_cc_proto
  modules::v2x::proto::v2x_traffic_light_cc_proto
  ${eigen}
)
add_library(modules::v2x::v2x_proxy::proto_adapter::proto_adapter  ALIAS   modules_v2x_v2x_proxy_proto_adapter_proto_adapter)