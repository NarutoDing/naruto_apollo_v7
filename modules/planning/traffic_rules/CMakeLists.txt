cmake_minimum_required(VERSION 3.16)

project(modules_planning_traffic_rules)
message("${Green} [info] modules_planning_traffic_rules cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_traffic_rules_traffic_rules  SHARED
  ${virtual_cc}
)
set_target_properties(modules_planning_traffic_rules_traffic_rules  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::traffic_rules::traffic_rules  ALIAS   modules_planning_traffic_rules_traffic_rules)

add_library(modules_planning_traffic_rules_traffic_decider  SHARED
  traffic_decider.cc
)
set_target_properties(modules_planning_traffic_rules_traffic_decider  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_traffic_rules_traffic_decider
  modules::planning::traffic_rules::traffic_rules
  modules::common::status::status
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::common::frame
  modules::planning::common::reference_line_info
  modules::planning::proto::traffic_rule_config_cc_proto
  modules::planning::tasks::task
)
add_library(modules::planning::traffic_rules::traffic_decider  ALIAS   modules_planning_traffic_rules_traffic_decider)

