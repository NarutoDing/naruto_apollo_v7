cmake_minimum_required(VERSION 3.16)

project(modules_planning_common)
message("${Green} [info] modules_planning_common cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_common_indexed_list  SHARED
  ${virtual_cc}
  indexed_list.h
)
set_target_properties(modules_planning_common_indexed_list  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_indexed_list
  modules::common::util::map_util
  ${boost}
)
add_library(modules::planning::common::indexed_list  ALIAS   modules_planning_common_indexed_list)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_common_indexed_queue  SHARED
  ${virtual_cc}
  indexed_queue.h
)
set_target_properties(modules_planning_common_indexed_queue  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_indexed_queue
  modules::common::util::map_util
)
add_library(modules::planning::common::indexed_queue  ALIAS   modules_planning_common_indexed_queue)

add_library(modules_planning_common_obstacle  SHARED
  obstacle.cc
)
set_target_properties(modules_planning_common_obstacle  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_obstacle
  modules::planning::common::indexed_list
  modules::common::configs::vehicle_config_helper
  modules::common::util::map_util
  modules::planning::common::speed::st_boundary
  modules::planning::proto::planning_cc_proto
  modules::planning::reference_line::reference_line
  modules::prediction::proto::feature_cc_proto
  modules::prediction::proto::lane_graph_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
  modules::prediction::proto::prediction_point_cc_proto
  modules::prediction::proto::scenario_cc_proto
)
add_library(modules::planning::common::obstacle  ALIAS   modules_planning_common_obstacle)

add_library(modules_planning_common_obstacle_blocking_analyzer  SHARED
  obstacle_blocking_analyzer.cc
)
set_target_properties(modules_planning_common_obstacle_blocking_analyzer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_obstacle_blocking_analyzer
  modules::planning::common::frame
  modules::common::configs::vehicle_config_helper
  modules::planning::reference_line::reference_line
)
add_library(modules::planning::common::obstacle_blocking_analyzer  ALIAS   modules_planning_common_obstacle_blocking_analyzer)

add_library(modules_planning_common_path_boundary  SHARED
  path_boundary.cc
)
set_target_properties(modules_planning_common_path_boundary  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::common::path_boundary  ALIAS   modules_planning_common_path_boundary)

add_library(modules_planning_common_planning_context  SHARED
  planning_context.cc
)
set_target_properties(modules_planning_common_planning_context  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_planning_context
  cyber::common::common
  modules::planning::common::path::path_data
  modules::planning::proto::planning_status_cc_proto
  ${eigen}
)
add_library(modules::planning::common::planning_context  ALIAS   modules_planning_common_planning_context)

add_library(modules_planning_common_path_decision  SHARED
  path_decision.cc
)
set_target_properties(modules_planning_common_path_decision  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_path_decision
  modules::planning::common::obstacle
  modules::planning::reference_line::reference_line
)
add_library(modules::planning::common::path_decision  ALIAS   modules_planning_common_path_decision)

add_library(modules_planning_common_planning_gflags  SHARED
  planning_gflags.cc
)
set_target_properties(modules_planning_common_planning_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_planning_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::planning::common::planning_gflags  ALIAS   modules_planning_common_planning_gflags)

add_library(modules_planning_common_reference_line_info  SHARED
  reference_line_info.cc
)
set_target_properties(modules_planning_common_reference_line_info  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_reference_line_info
  modules::planning::common::ego_info
  modules::planning::common::path_boundary
  modules::planning::common::path_decision
  modules::planning::common::planning_gflags
  modules::planning::common::st_graph_data
  cyber::common::log
  modules::common::math::math
  modules::common::proto::pnc_point_cc_proto
  modules::common::util::point_factory
  modules::common::vehicle_state::vehicle_state_provider
  modules::map::pnc_map::pnc_map
  modules::map::proto::map_cc_proto
  modules::planning::common::path::path_data
  modules::planning::common::speed::speed_data
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::common::trajectory::publishable_trajectory
  modules::planning::proto::lattice_structure_cc_proto
  modules::planning::reference_line::reference_line
  ${eigen}
)
add_library(modules::planning::common::reference_line_info  ALIAS   modules_planning_common_reference_line_info)

add_library(modules_planning_common_speed_profile_generator  SHARED
  speed_profile_generator.cc
)
set_target_properties(modules_planning_common_speed_profile_generator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_speed_profile_generator
  modules::planning::common::frame
  modules::planning::common::reference_line_info
  modules::common::proto::pnc_point_cc_proto
  modules::planning::common::speed::speed_data
  modules::planning::math::curve1d::curve1d
  modules::planning::math::curve1d::polynomial_curve1d
  modules::planning::math::curve1d::quartic_polynomial_curve1d
  modules::planning::math::curve1d::quintic_polynomial_curve1d
  modules::planning::math::piecewise_jerk::piecewise_jerk_speed_problem
  modules::planning::proto::planning_config_cc_proto
)
add_library(modules::planning::common::speed_profile_generator  ALIAS   modules_planning_common_speed_profile_generator)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_common_local_view  SHARED
  ${virtual_cc}
  local_view.h
)
set_target_properties(modules_planning_common_local_view  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_local_view
  modules::canbus::proto::chassis_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::map::relative_map::proto::navigation_cc_proto
  modules::perception::proto::traffic_light_detection_cc_proto
  modules::planning::proto::pad_msg_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
  modules::routing::proto::routing_cc_proto
  modules::storytelling::proto::story_cc_proto
)
add_library(modules::planning::common::local_view  ALIAS   modules_planning_common_local_view)

add_library(modules_planning_common_frame  SHARED
  frame.cc
)
set_target_properties(modules_planning_common_frame  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_frame
  modules::planning::common::feature_output
  modules::planning::common::local_view
  modules::planning::common::obstacle
  modules::planning::common::open_space_info
  modules::planning::common::reference_line_info
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::monitor_log::monitor_log
  modules::common::vehicle_state::vehicle_state_provider
  modules::map::hdmap::hdmap_util
  modules::map::pnc_map::pnc_map
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::common::trajectory::publishable_trajectory
  modules::planning::common::util::util_lib
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::reference_line::reference_line_provider
  ${eigen}
)
add_library(modules::planning::common::frame  ALIAS   modules_planning_common_frame)

add_library(modules_planning_common_history  SHARED
  history.cc
)
set_target_properties(modules_planning_common_history  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_history
  modules::planning::common::planning_gflags
  cyber::common::common
  modules::planning::proto::decision_cc_proto
  modules::planning::proto::planning_cc_proto
  ${eigen}
)
add_library(modules::planning::common::history  ALIAS   modules_planning_common_history)

add_library(modules_planning_common_speed_limit  SHARED
  speed_limit.cc
)
set_target_properties(modules_planning_common_speed_limit  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_speed_limit
  modules::common::math::math
)
add_library(modules::planning::common::speed_limit  ALIAS   modules_planning_common_speed_limit)

add_library(modules_planning_common_ego_info  SHARED
  ego_info.cc
)
set_target_properties(modules_planning_common_ego_info  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_ego_info
  modules::planning::common::obstacle
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::math::geometry
  modules::common::vehicle_state::proto::vehicle_state_cc_proto
  modules::planning::reference_line::reference_line
  modules::prediction::proto::feature_cc_proto
  modules::prediction::proto::lane_graph_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
  modules::prediction::proto::prediction_point_cc_proto
  modules::prediction::proto::scenario_cc_proto
  ${eigen}
)
add_library(modules::planning::common::ego_info  ALIAS   modules_planning_common_ego_info)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_common_planning_common  SHARED
  ${virtual_cc}
)
set_target_properties(modules_planning_common_planning_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_planning_common
  modules::planning::common::ego_info
  modules::planning::common::frame
  modules::planning::common::planning_gflags
  modules::planning::common::speed_limit
  modules::planning::common::st_graph_data
  cyber::common::log
  modules::localization::common::localization_common
  modules::localization::proto::localization_cc_proto
  ${eigen}
)
add_library(modules::planning::common::planning_common  ALIAS   modules_planning_common_planning_common)

add_library(modules_planning_common_trajectory_stitcher  SHARED
  trajectory_stitcher.cc
)
set_target_properties(modules_planning_common_trajectory_stitcher  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory_stitcher
  cyber::common::log
  modules::common::proto::pnc_point_cc_proto
  modules::common::vehicle_model::vehicle_model
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory::publishable_trajectory
  modules::planning::reference_line::reference_line
  ${absl}
)
add_library(modules::planning::common::trajectory_stitcher  ALIAS   modules_planning_common_trajectory_stitcher)

add_library(modules_planning_common_open_space_info  SHARED
  open_space_info.cc
)
set_target_properties(modules_planning_common_open_space_info  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_open_space_info
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::vehicle_state::proto::vehicle_state_cc_proto
  modules::map::hdmap::hdmap_util
  modules::map::pnc_map::pnc_map
  modules::planning::common::indexed_queue
  modules::planning::common::obstacle
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::common::trajectory::publishable_trajectory
  ${eigen}
)
add_library(modules::planning::common::open_space_info  ALIAS   modules_planning_common_open_space_info)

add_library(modules_planning_common_st_graph_data  SHARED
  st_graph_data.cc
)
set_target_properties(modules_planning_common_st_graph_data  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_st_graph_data
  modules::planning::common::planning_gflags
  modules::planning::common::speed_limit
  modules::planning::common::speed::st_boundary
  modules::planning::proto::st_drivable_boundary_cc_proto
)
add_library(modules::planning::common::st_graph_data  ALIAS   modules_planning_common_st_graph_data)

add_library(modules_planning_common_feature_output  SHARED
  feature_output.cc
)
set_target_properties(modules_planning_common_feature_output  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_feature_output
  cyber::cyber
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::learning_data_cc_proto
)
add_library(modules::planning::common::feature_output  ALIAS   modules_planning_common_feature_output)

add_library(modules_planning_common_message_process  SHARED
  message_process.cc
)
set_target_properties(modules_planning_common_message_process  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_message_process
  modules::planning::common::dependency_injector
  modules::planning::common::feature_output
  cyber::cyber
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::configs::config_gflags
  modules::dreamview::proto::hmi_status_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::perception::proto::perception_obstacle_cc_proto
  modules::perception::proto::traffic_light_detection_cc_proto
  modules::planning::common::util::math_util_lib
  modules::planning::common::util::util_lib
  modules::planning::proto::learning_data_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
  modules::prediction::util::data_extraction
  modules::routing::proto::routing_cc_proto
  modules::storytelling::proto::story_cc_proto
  ${boost}
  ${absl}
)
add_library(modules::planning::common::message_process  ALIAS   modules_planning_common_message_process)

add_library(modules_planning_common_trajectory_evaluator  SHARED
  trajectory_evaluator.cc
)
set_target_properties(modules_planning_common_trajectory_evaluator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_trajectory_evaluator
  cyber::cyber
  modules::planning::common::planning_gflags
  modules::planning::common::util::util_lib
  modules::planning::pipeline::evaluator_logger
  modules::planning::proto::learning_data_cc_proto
)
add_library(modules::planning::common::trajectory_evaluator  ALIAS   modules_planning_common_trajectory_evaluator)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_common_dependency_injector  SHARED
  ${virtual_cc}
  dependency_injector.h
)
set_target_properties(modules_planning_common_dependency_injector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_dependency_injector
  modules::planning::common::ego_info
  modules::planning::common::frame
  modules::planning::common::history
  modules::planning::common::learning_based_data
  modules::planning::common::planning_context
)
add_library(modules::planning::common::dependency_injector  ALIAS   modules_planning_common_dependency_injector)

add_library(modules_planning_common_learning_based_data  SHARED
  learning_based_data.cc
)
set_target_properties(modules_planning_common_learning_based_data  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_common_learning_based_data
  cyber::common::common
  modules::planning::proto::learning_data_cc_proto
)
add_library(modules::planning::common::learning_based_data  ALIAS   modules_planning_common_learning_based_data)

