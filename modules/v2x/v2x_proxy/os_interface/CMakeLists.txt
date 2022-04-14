cmake_minimum_required(VERSION 3.16)

project(modules_v2x_v2x_proxy_os_interface)
message("${Green} [info] modules_v2x_v2x_proxy_os_interface cmakelist ${ColourReset}")

add_library(modules_v2x_v2x_proxy_os_interface_os_interface  SHARED
  os_interface.cc
)
set_target_properties(modules_v2x_v2x_proxy_os_interface_os_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_v2x_proxy_os_interface_os_interface
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::localization::proto::localization_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
  modules::planning::proto::planning_cc_proto
  modules::v2x::common::v2x_proxy_gflags
  modules::v2x::proto::v2x_obstacles_cc_proto
  modules::v2x::proto::v2x_obu_rsi_cc_proto
  modules::v2x::proto::v2x_obu_traffic_light_cc_proto
  modules::v2x::proto::v2x_traffic_light_cc_proto
)
add_library(modules::v2x::v2x_proxy::os_interface::os_interface  ALIAS   modules_v2x_v2x_proxy_os_interface_os_interface)

