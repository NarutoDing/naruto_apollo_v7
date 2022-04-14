cmake_minimum_required(VERSION 3.16)

project(modules_prediction_common)
message("${Green} [info] modules_prediction_common cmakelist ${ColourReset}")

add_library(modules_prediction_common_prediction_gflags  SHARED
  prediction_gflags.cc
)
set_target_properties(modules_prediction_common_prediction_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_prediction_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::prediction::common::prediction_gflags  ALIAS   modules_prediction_common_prediction_gflags)

add_library(modules_prediction_common_prediction_system_gflags  SHARED
  prediction_system_gflags.cc
)
set_target_properties(modules_prediction_common_prediction_system_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_prediction_system_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::prediction::common::prediction_system_gflags  ALIAS   modules_prediction_common_prediction_system_gflags)

add_library(modules_prediction_common_prediction_util  SHARED
  prediction_util.cc
)
set_target_properties(modules_prediction_common_prediction_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_prediction_util
  modules::prediction::common::prediction_gflags
  modules::prediction::common::prediction_map
)
add_library(modules::prediction::common::prediction_util  ALIAS   modules_prediction_common_prediction_util)

add_library(modules_prediction_common_prediction_map  SHARED
  prediction_map.cc
)
set_target_properties(modules_prediction_common_prediction_map  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_prediction_map
  modules::prediction::common::prediction_gflags
  modules::map::pnc_map::pnc_map
)
add_library(modules::prediction::common::prediction_map  ALIAS   modules_prediction_common_prediction_map)

add_library(modules_prediction_common_feature_output  SHARED
  feature_output.cc
)
set_target_properties(modules_prediction_common_feature_output  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_feature_output
  modules::common::util::util
  modules::prediction::common::prediction_gflags
  modules::prediction::container::obstacles::obstacle
  modules::prediction::proto::offline_features_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
)
add_library(modules::prediction::common::feature_output  ALIAS   modules_prediction_common_feature_output)

add_library(modules_prediction_common_road_graph  SHARED
  road_graph.cc
)
set_target_properties(modules_prediction_common_road_graph  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_road_graph
  modules::prediction::common::prediction_map
  modules::prediction::common::prediction_constants
  modules::prediction::common::prediction_gflags
  modules::prediction::common::prediction_system_gflags
  modules::prediction::proto::lane_graph_cc_proto
)
add_library(modules::prediction::common::road_graph  ALIAS   modules_prediction_common_road_graph)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_prediction_common_kml_map_based_test  SHARED
  ${virtual_cc}
  kml_map_based_test.h
)
set_target_properties(modules_prediction_common_kml_map_based_test  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::prediction::common::kml_map_based_test  ALIAS   modules_prediction_common_kml_map_based_test)

add_library(modules_prediction_common_validation_checker  SHARED
  validation_checker.cc
)
set_target_properties(modules_prediction_common_validation_checker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_validation_checker
  modules::common::math::math
  modules::prediction::common::prediction_gflags
  modules::prediction::proto::lane_graph_cc_proto
)
add_library(modules::prediction::common::validation_checker  ALIAS   modules_prediction_common_validation_checker)

add_library(modules_prediction_common_environment_features  SHARED
  environment_features.cc
)
set_target_properties(modules_prediction_common_environment_features  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_environment_features
  cyber::cyber
  modules::common::proto::geometry_cc_proto
)
add_library(modules::prediction::common::environment_features  ALIAS   modules_prediction_common_environment_features)

add_library(modules_prediction_common_junction_analyzer  SHARED
  junction_analyzer.cc
)
set_target_properties(modules_prediction_common_junction_analyzer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_junction_analyzer
  modules::prediction::common::prediction_map
  modules::prediction::proto::feature_cc_proto
)
add_library(modules::prediction::common::junction_analyzer  ALIAS   modules_prediction_common_junction_analyzer)

add_library(modules_prediction_common_message_process  SHARED
  message_process.cc
)
set_target_properties(modules_prediction_common_message_process  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_message_process
  modules::prediction::common::semantic_map
  cyber::common::file
  cyber::proto::record_cc_proto
  modules::common::adapters::adapter_gflags
  modules::prediction::evaluator::evaluator_manager
  modules::prediction::predictor::predictor_manager
  modules::prediction::proto::offline_features_cc_proto
  modules::prediction::scenario::scenario_manager
  modules::prediction::util::data_extraction
)
add_library(modules::prediction::common::message_process  ALIAS   modules_prediction_common_message_process)

add_library(modules_prediction_common_prediction_thread_pool  SHARED
  prediction_thread_pool.cc
)
set_target_properties(modules_prediction_common_prediction_thread_pool  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_prediction_thread_pool
  cyber::base::base
  cyber::common::common
)
add_library(modules::prediction::common::prediction_thread_pool  ALIAS   modules_prediction_common_prediction_thread_pool)

add_library(modules_prediction_common_semantic_map  SHARED
  semantic_map.cc
)
set_target_properties(modules_prediction_common_semantic_map  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_common_semantic_map
  modules::prediction::common::prediction_gflags
  cyber::common::common
  modules::common::configs::config_gflags
  modules::common::util::util
  modules::prediction::container::container_manager
  modules::prediction::container::pose::pose_container
  modules::prediction::proto::feature_cc_proto
  ${opencv}
)
add_library(modules::prediction::common::semantic_map  ALIAS   modules_prediction_common_semantic_map)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_prediction_common_prediction_constants  SHARED
  ${virtual_cc}
  prediction_constants.h
)
set_target_properties(modules_prediction_common_prediction_constants  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::prediction::common::prediction_constants  ALIAS   modules_prediction_common_prediction_constants)

