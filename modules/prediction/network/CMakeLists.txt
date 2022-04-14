cmake_minimum_required(VERSION 3.16)

project(modules_prediction_network)
message("${Green} [info] modules_prediction_network cmakelist ${ColourReset}")

add_library(modules_prediction_network_net_util  SHARED
  net_util.cc
)
set_target_properties(modules_prediction_network_net_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_network_net_util
  cyber::common::log
  modules::prediction::proto::network_layers_cc_proto
  ${eigen}
)
add_library(modules::prediction::network::net_util  ALIAS   modules_prediction_network_net_util)

add_library(modules_prediction_network_net_layer  SHARED
  net_layer.cc
)
set_target_properties(modules_prediction_network_net_layer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_network_net_layer
  modules::prediction::network::net_util
)
add_library(modules::prediction::network::net_layer  ALIAS   modules_prediction_network_net_layer)

add_library(modules_prediction_network_net_model  SHARED
  net_model.cc
)
set_target_properties(modules_prediction_network_net_model  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_network_net_model
  modules::common::util::util
  modules::prediction::network::net_layer
  modules::prediction::proto::network_model_cc_proto
)
add_library(modules::prediction::network::net_model  ALIAS   modules_prediction_network_net_model)

