cmake_minimum_required(VERSION 3.16)

project(modules_prediction_evaluator_vehicle)
message("${Green} [info] modules_prediction_evaluator_vehicle cmakelist ${ColourReset}")

add_library(modules_prediction_evaluator_vehicle_mlp_evaluator  SHARED
  mlp_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_mlp_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_mlp_evaluator
  modules::prediction::common::feature_output
  modules::prediction::common::prediction_util
  modules::prediction::common::validation_checker
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  modules::prediction::proto::fnn_vehicle_model_cc_proto
)
add_library(modules::prediction::evaluator::vehicle::mlp_evaluator  ALIAS   modules_prediction_evaluator_vehicle_mlp_evaluator)

add_library(modules_prediction_evaluator_vehicle_cost_evaluator  SHARED
  cost_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_cost_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_cost_evaluator
  modules::prediction::common::prediction_util
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
)
add_library(modules::prediction::evaluator::vehicle::cost_evaluator  ALIAS   modules_prediction_evaluator_vehicle_cost_evaluator)

add_library(modules_prediction_evaluator_vehicle_junction_mlp_evaluator  SHARED
  junction_mlp_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_junction_mlp_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_junction_mlp_evaluator
  modules::common::math::geometry
  modules::prediction::common::feature_output
  modules::prediction::common::prediction_util
  modules::prediction::container::container_manager
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  ${libtorch}
)
add_library(modules::prediction::evaluator::vehicle::junction_mlp_evaluator  ALIAS   modules_prediction_evaluator_vehicle_junction_mlp_evaluator)

add_library(modules_prediction_evaluator_vehicle_junction_map_evaluator  SHARED
  junction_map_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_junction_map_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_junction_map_evaluator
  modules::prediction::common::prediction_util
  modules::prediction::common::semantic_map
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  ${libtorch}
)
add_library(modules::prediction::evaluator::vehicle::junction_map_evaluator  ALIAS   modules_prediction_evaluator_vehicle_junction_map_evaluator)

add_library(modules_prediction_evaluator_vehicle_cruise_mlp_evaluator  SHARED
  cruise_mlp_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_cruise_mlp_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_cruise_mlp_evaluator
  modules::prediction::common::prediction_util
  modules::prediction::container::container_manager
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  ${libtorch}
)
add_library(modules::prediction::evaluator::vehicle::cruise_mlp_evaluator  ALIAS   modules_prediction_evaluator_vehicle_cruise_mlp_evaluator)

add_library(modules_prediction_evaluator_vehicle_lane_scanning_evaluator  SHARED
  lane_scanning_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_lane_scanning_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_lane_scanning_evaluator
  modules::prediction::container::container_manager
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  ${libtorch}
)
add_library(modules::prediction::evaluator::vehicle::lane_scanning_evaluator  ALIAS   modules_prediction_evaluator_vehicle_lane_scanning_evaluator)

add_library(modules_prediction_evaluator_vehicle_lane_aggregating_evaluator  SHARED
  lane_aggregating_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_lane_aggregating_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_lane_aggregating_evaluator
  modules::prediction::container::container_manager
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  ${libtorch}
)
add_library(modules::prediction::evaluator::vehicle::lane_aggregating_evaluator  ALIAS   modules_prediction_evaluator_vehicle_lane_aggregating_evaluator)

add_library(modules_prediction_evaluator_vehicle_semantic_lstm_evaluator  SHARED
  semantic_lstm_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_semantic_lstm_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_semantic_lstm_evaluator
  modules::prediction::common::prediction_util
  modules::prediction::common::semantic_map
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  ${libtorch}
  ${eigen}
)
add_library(modules::prediction::evaluator::vehicle::semantic_lstm_evaluator  ALIAS   modules_prediction_evaluator_vehicle_semantic_lstm_evaluator)

add_library(modules_prediction_evaluator_vehicle_jointly_prediction_planning_evaluator  SHARED
  jointly_prediction_planning_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_jointly_prediction_planning_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_jointly_prediction_planning_evaluator
  modules::prediction::common::prediction_util
  modules::prediction::common::semantic_map
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  modules::prediction::pipeline::vector_net
  ${libtorch}
  ${eigen}
)
add_library(modules::prediction::evaluator::vehicle::jointly_prediction_planning_evaluator  ALIAS   modules_prediction_evaluator_vehicle_jointly_prediction_planning_evaluator)

add_library(modules_prediction_evaluator_vehicle_vectornet_evaluator  SHARED
  vectornet_evaluator.cc
)
set_target_properties(modules_prediction_evaluator_vehicle_vectornet_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_evaluator_vehicle_vectornet_evaluator
  modules::prediction::common::prediction_util
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::evaluator::evaluator
  modules::prediction::pipeline::vector_net
  ${libtorch}
  ${eigen}
)
add_library(modules::prediction::evaluator::vehicle::vectornet_evaluator  ALIAS   modules_prediction_evaluator_vehicle_vectornet_evaluator)

