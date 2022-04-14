cmake_minimum_required(VERSION 3.16)

project(modules_planning)
message("${Green} [info] modules_planning cmakelist ${ColourReset}")

add_library(modules_planning_planning_component_lib  SHARED
  planning_component.cc
)
set_target_properties(modules_planning_planning_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_planning_component_lib
  modules::planning::navi_planning
  modules::planning::on_lane_planning
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::localization::proto::localization_cc_proto
  modules::map::relative_map::proto::navigation_cc_proto
  modules::perception::proto::traffic_light_detection_cc_proto
  modules::planning::common::history
  modules::planning::common::message_process
  modules::planning::proto::planning_cc_proto
  modules::prediction::proto::prediction_obstacle_cc_proto
  modules::storytelling::proto::story_cc_proto
)
add_library(modules::planning::planning_component_lib  ALIAS   modules_planning_planning_component_lib)

add_library(modules_planning_planning_base  SHARED
  planning_base.cc
)
set_target_properties(modules_planning_planning_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_planning_base
  cyber::cyber
  modules::common::configs::config_gflags
  modules::common::math::quaternion
  modules::common::proto::pnc_point_cc_proto
  modules::common::util::future
  modules::common::util::message_util
  modules::common::vehicle_state::vehicle_state_provider
  modules::localization::proto::localization_cc_proto
  modules::map::hdmap::hdmap_util
  modules::perception::proto::traffic_light_detection_cc_proto
  modules::planning::common::history
  modules::planning::common::planning_common
  modules::planning::common::planning_gflags
  modules::planning::common::trajectory_stitcher
  modules::planning::common::smoothers::smoother
  modules::planning::common::util::util_lib
  modules::planning::planner::planner
  modules::planning::planner::planner_dispatcher
  modules::planning::proto::planning_cc_proto
  modules::planning::proto::planning_config_cc_proto
  modules::planning::proto::traffic_rule_config_cc_proto
  modules::planning::tasks::task_factory
  modules::planning::traffic_rules::traffic_decider
  modules::prediction::proto::prediction_obstacle_cc_proto
)
add_library(modules::planning::planning_base  ALIAS   modules_planning_planning_base)

add_library(modules_planning_navi_planning  SHARED
  navi_planning.cc
)
set_target_properties(modules_planning_navi_planning  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_navi_planning
  modules::planning::planning_base
)
add_library(modules::planning::navi_planning  ALIAS   modules_planning_navi_planning)

add_library(modules_planning_on_lane_planning  SHARED
  on_lane_planning.cc
)
set_target_properties(modules_planning_on_lane_planning  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_on_lane_planning
  modules::planning::planning_base
  cyber::common::log
  modules::planning::learning_based::img_feature_renderer::birdview_img_feature_renderer
)
add_library(modules::planning::on_lane_planning  ALIAS   modules_planning_on_lane_planning)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libplanning_component  SHARED
  ${virtual_cc}
)
set_target_properties(libplanning_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libplanning_component
  modules::planning::planning_component_lib
)
