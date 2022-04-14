cmake_minimum_required(VERSION 3.16)

project(modules_planning_proto)
message("${Green} [info] modules_planning_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/planning/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_planning_proto_sl_boundary_cc_proto  SHARED
  sl_boundary.pb.cc
)
set_target_properties(modules_planning_proto_sl_boundary_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_sl_boundary_cc_proto
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::planning::proto::sl_boundary_cc_proto  ALIAS   modules_planning_proto_sl_boundary_cc_proto)

add_library(modules_planning_proto_lattice_structure_cc_proto  SHARED
  lattice_structure.pb.cc
)
set_target_properties(modules_planning_proto_lattice_structure_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::lattice_structure_cc_proto  ALIAS   modules_planning_proto_lattice_structure_cc_proto)

add_library(modules_planning_proto_decision_cc_proto  SHARED
  decision.pb.cc
)
set_target_properties(modules_planning_proto_decision_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_decision_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::vehicle_signal_cc_proto
  modules::routing::proto::routing_cc_proto
)
add_library(modules::planning::proto::decision_cc_proto  ALIAS   modules_planning_proto_decision_cc_proto)

add_library(modules_planning_proto_planning_status_cc_proto  SHARED
  planning_status.pb.cc
)
set_target_properties(modules_planning_proto_planning_status_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_planning_status_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::routing::proto::routing_cc_proto
)
add_library(modules::planning::proto::planning_status_cc_proto  ALIAS   modules_planning_proto_planning_status_cc_proto)

add_library(modules_planning_proto_planner_open_space_config_cc_proto  SHARED
  planner_open_space_config.pb.cc
)
set_target_properties(modules_planning_proto_planner_open_space_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_planner_open_space_config_cc_proto
  modules::planning::proto::task_config_cc_proto
  modules::planning::proto::math::fem_pos_deviation_smoother_config_cc_proto
)
add_library(modules::planning::proto::planner_open_space_config_cc_proto  ALIAS   modules_planning_proto_planner_open_space_config_cc_proto)

add_library(modules_planning_proto_auto_tuning_model_input_cc_proto  SHARED
  auto_tuning_model_input.pb.cc
)
set_target_properties(modules_planning_proto_auto_tuning_model_input_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::auto_tuning_model_input_cc_proto  ALIAS   modules_planning_proto_auto_tuning_model_input_cc_proto)

add_library(modules_planning_proto_planning_semantic_map_config_cc_proto  SHARED
  planning_semantic_map_config.pb.cc
)
set_target_properties(modules_planning_proto_planning_semantic_map_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::planning_semantic_map_config_cc_proto  ALIAS   modules_planning_proto_planning_semantic_map_config_cc_proto)

add_library(modules_planning_proto_traffic_rule_config_cc_proto  SHARED
  traffic_rule_config.pb.cc
)
set_target_properties(modules_planning_proto_traffic_rule_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::traffic_rule_config_cc_proto  ALIAS   modules_planning_proto_traffic_rule_config_cc_proto)

add_library(modules_planning_proto_planning_stats_cc_proto  SHARED
  planning_stats.pb.cc
)
set_target_properties(modules_planning_proto_planning_stats_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::planning_stats_cc_proto  ALIAS   modules_planning_proto_planning_stats_cc_proto)

add_library(modules_planning_proto_open_space_task_config_cc_proto  SHARED
  open_space_task_config.pb.cc
)
set_target_properties(modules_planning_proto_open_space_task_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_open_space_task_config_cc_proto
  modules::planning::proto::planner_open_space_config_cc_proto
)
add_library(modules::planning::proto::open_space_task_config_cc_proto  ALIAS   modules_planning_proto_open_space_task_config_cc_proto)

add_library(modules_planning_proto_reference_line_smoother_config_cc_proto  SHARED
  reference_line_smoother_config.pb.cc
)
set_target_properties(modules_planning_proto_reference_line_smoother_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_reference_line_smoother_config_cc_proto
  modules::planning::proto::math::cos_theta_smoother_config_cc_proto
  modules::planning::proto::math::fem_pos_deviation_smoother_config_cc_proto
)
add_library(modules::planning::proto::reference_line_smoother_config_cc_proto  ALIAS   modules_planning_proto_reference_line_smoother_config_cc_proto)

add_library(modules_planning_proto_task_config_cc_proto  SHARED
  task_config.pb.cc
)
set_target_properties(modules_planning_proto_task_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::task_config_cc_proto  ALIAS   modules_planning_proto_task_config_cc_proto)

add_library(modules_planning_proto_learning_data_cc_proto  SHARED
  learning_data.pb.cc
)
set_target_properties(modules_planning_proto_learning_data_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_learning_data_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::map::proto::map_lane_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
  modules::perception::proto::traffic_light_detection_cc_proto
  modules::prediction::proto::feature_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
  modules::routing::proto::routing_cc_proto
)
add_library(modules::planning::proto::learning_data_cc_proto  ALIAS   modules_planning_proto_learning_data_cc_proto)

add_library(modules_planning_proto_planning_cc_proto  SHARED
  planning.pb.cc
)
set_target_properties(modules_planning_proto_planning_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_planning_cc_proto
  modules::planning::proto::decision_cc_proto
  modules::planning::proto::planning_internal_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::proto::drive_state_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::map::proto::map_id_cc_proto
)
add_library(modules::planning::proto::planning_cc_proto  ALIAS   modules_planning_proto_planning_cc_proto)

add_library(modules_planning_proto_planning_internal_cc_proto  SHARED
  planning_internal.pb.cc
)
set_target_properties(modules_planning_proto_planning_internal_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_planning_internal_cc_proto
  modules::planning::proto::decision_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::proto::sl_boundary_cc_proto
  modules::canbus::proto::chassis_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
  modules::common::proto::pnc_point_cc_proto
  modules::dreamview::proto::chart_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::map::relative_map::proto::navigation_cc_proto
  modules::perception::proto::traffic_light_detection_cc_proto
  modules::routing::proto::routing_cc_proto
)
add_library(modules::planning::proto::planning_internal_cc_proto  ALIAS   modules_planning_proto_planning_internal_cc_proto)

add_library(modules_planning_proto_planning_config_cc_proto  SHARED
  planning_config.pb.cc
)
set_target_properties(modules_planning_proto_planning_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_planning_config_cc_proto
  modules::planning::proto::open_space_task_config_cc_proto
  modules::planning::proto::task_config_cc_proto
)
add_library(modules::planning::proto::planning_config_cc_proto  ALIAS   modules_planning_proto_planning_config_cc_proto)

add_library(modules_planning_proto_pad_msg_cc_proto  SHARED
  pad_msg.pb.cc
)
set_target_properties(modules_planning_proto_pad_msg_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_pad_msg_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::planning::proto::pad_msg_cc_proto  ALIAS   modules_planning_proto_pad_msg_cc_proto)

add_library(modules_planning_proto_auto_tuning_raw_feature_cc_proto  SHARED
  auto_tuning_raw_feature.pb.cc
)
set_target_properties(modules_planning_proto_auto_tuning_raw_feature_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_proto_auto_tuning_raw_feature_cc_proto
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::planning::proto::auto_tuning_raw_feature_cc_proto  ALIAS   modules_planning_proto_auto_tuning_raw_feature_cc_proto)

add_library(modules_planning_proto_ipopt_return_status_cc_proto  SHARED
  ipopt_return_status.pb.cc
)
set_target_properties(modules_planning_proto_ipopt_return_status_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::ipopt_return_status_cc_proto  ALIAS   modules_planning_proto_ipopt_return_status_cc_proto)

add_library(modules_planning_proto_st_drivable_boundary_cc_proto  SHARED
  st_drivable_boundary.pb.cc
)
set_target_properties(modules_planning_proto_st_drivable_boundary_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::st_drivable_boundary_cc_proto  ALIAS   modules_planning_proto_st_drivable_boundary_cc_proto)

