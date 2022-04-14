cmake_minimum_required(VERSION 3.16)

project(modules_prediction_network_rnn_model)
message("${Green} [info] modules_prediction_network_rnn_model cmakelist ${ColourReset}")

add_library(modules_prediction_network_rnn_model_rnn_model  SHARED
  rnn_model.cc
)
set_target_properties(modules_prediction_network_rnn_model_rnn_model  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_network_rnn_model_rnn_model
  cyber::base::macros
  cyber::common::macros
  modules::prediction::network::net_model
)
add_library(modules::prediction::network::rnn_model::rnn_model  ALIAS   modules_prediction_network_rnn_model_rnn_model)

