cmake_minimum_required(VERSION 3.16)

project(modules_prediction_proto)
message("${Green} [info] modules_prediction_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/prediction/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_prediction_proto_prediction_conf_cc_proto  SHARED
  prediction_conf.pb.cc
)
set_target_properties(modules_prediction_proto_prediction_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_proto_prediction_conf_cc_proto
  modules::prediction::proto::feature_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
)
add_library(modules::prediction::proto::prediction_conf_cc_proto  ALIAS   modules_prediction_proto_prediction_conf_cc_proto)

add_library(modules_prediction_proto_lane_graph_cc_proto  SHARED
  lane_graph.pb.cc
)
set_target_properties(modules_prediction_proto_lane_graph_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_proto_lane_graph_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::map::proto::map_lane_cc_proto
)
add_library(modules::prediction::proto::lane_graph_cc_proto  ALIAS   modules_prediction_proto_lane_graph_cc_proto)

add_library(modules_prediction_proto_prediction_obstacle_cc_proto  SHARED
  prediction_obstacle.pb.cc
)
set_target_properties(modules_prediction_proto_prediction_obstacle_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_proto_prediction_obstacle_cc_proto
  modules::prediction::proto::feature_cc_proto
  modules::prediction::proto::scenario_cc_proto
  modules::common::proto::error_code_cc_proto
  modules::common::proto::header_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
)
add_library(modules::prediction::proto::prediction_obstacle_cc_proto  ALIAS   modules_prediction_proto_prediction_obstacle_cc_proto)

add_library(modules_prediction_proto_fnn_vehicle_model_cc_proto  SHARED
  fnn_vehicle_model.pb.cc
)
set_target_properties(modules_prediction_proto_fnn_vehicle_model_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_proto_fnn_vehicle_model_cc_proto
  modules::prediction::proto::fnn_model_base_cc_proto
)
add_library(modules::prediction::proto::fnn_vehicle_model_cc_proto  ALIAS   modules_prediction_proto_fnn_vehicle_model_cc_proto)

add_library(modules_prediction_proto_offline_features_cc_proto  SHARED
  offline_features.pb.cc
)
set_target_properties(modules_prediction_proto_offline_features_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_proto_offline_features_cc_proto
  modules::prediction::proto::feature_cc_proto
  modules::prediction::proto::prediction_conf_cc_proto
  modules::prediction::proto::scenario_cc_proto
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::prediction::proto::offline_features_cc_proto  ALIAS   modules_prediction_proto_offline_features_cc_proto)

add_library(modules_prediction_proto_scenario_cc_proto  SHARED
  scenario.pb.cc
)
set_target_properties(modules_prediction_proto_scenario_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::prediction::proto::scenario_cc_proto  ALIAS   modules_prediction_proto_scenario_cc_proto)

add_library(modules_prediction_proto_feature_cc_proto  SHARED
  feature.pb.cc
)
set_target_properties(modules_prediction_proto_feature_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_proto_feature_cc_proto
  modules::prediction::proto::lane_graph_cc_proto
  modules::prediction::proto::prediction_point_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::map::proto::map_lane_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
)
add_library(modules::prediction::proto::feature_cc_proto  ALIAS   modules_prediction_proto_feature_cc_proto)

add_library(modules_prediction_proto_network_layers_cc_proto  SHARED
  network_layers.pb.cc
)
set_target_properties(modules_prediction_proto_network_layers_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::prediction::proto::network_layers_cc_proto  ALIAS   modules_prediction_proto_network_layers_cc_proto)

add_library(modules_prediction_proto_prediction_point_cc_proto  SHARED
  prediction_point.pb.cc
)
set_target_properties(modules_prediction_proto_prediction_point_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::prediction::proto::prediction_point_cc_proto  ALIAS   modules_prediction_proto_prediction_point_cc_proto)

add_library(modules_prediction_proto_fnn_model_base_cc_proto  SHARED
  fnn_model_base.pb.cc
)
set_target_properties(modules_prediction_proto_fnn_model_base_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::prediction::proto::fnn_model_base_cc_proto  ALIAS   modules_prediction_proto_fnn_model_base_cc_proto)

add_library(modules_prediction_proto_network_model_cc_proto  SHARED
  network_model.pb.cc
)
set_target_properties(modules_prediction_proto_network_model_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_proto_network_model_cc_proto
  modules::prediction::proto::network_layers_cc_proto
)
add_library(modules::prediction::proto::network_model_cc_proto  ALIAS   modules_prediction_proto_network_model_cc_proto)

add_library(modules_prediction_proto_vector_net_cc_proto  SHARED
  vector_net.pb.cc
)
set_target_properties(modules_prediction_proto_vector_net_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::prediction::proto::vector_net_cc_proto  ALIAS   modules_prediction_proto_vector_net_cc_proto)

