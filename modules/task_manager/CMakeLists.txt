cmake_minimum_required(VERSION 3.16)

project(modules_task_manager)
message("${Green} [info] modules_task_manager cmakelist ${ColourReset}")

add_library(modules_task_manager_cycle_routing_manager_lib  SHARED
  cycle_routing_manager.cc
)
set_target_properties(modules_task_manager_cycle_routing_manager_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_task_manager_cycle_routing_manager_lib
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::dreamview::backend::map::map_service
  modules::localization::proto::localization_cc_proto
  modules::task_manager::common::task_manager_gflags
  modules::task_manager::proto::task_manager_cc_proto
)
add_library(modules::task_manager::cycle_routing_manager_lib  ALIAS   modules_task_manager_cycle_routing_manager_lib)

add_library(modules_task_manager_parking_routing_manager_lib  SHARED
  parking_routing_manager.cc
)
set_target_properties(modules_task_manager_parking_routing_manager_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_task_manager_parking_routing_manager_lib
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::dreamview::backend::map::map_service
  modules::common::configs::vehicle_config_helper
  modules::task_manager::common::task_manager_gflags
  modules::task_manager::proto::task_manager_cc_proto
  modules::task_manager::proto::task_manager_config_cc_proto
)
add_library(modules::task_manager::parking_routing_manager_lib  ALIAS   modules_task_manager_parking_routing_manager_lib)

add_library(modules_task_manager_dead_end_routing_manager_lib  SHARED
  dead_end_routing_manager.cc
)
set_target_properties(modules_task_manager_dead_end_routing_manager_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_task_manager_dead_end_routing_manager_lib
  modules::common::monitor_log::monitor_log
  modules::common::status::status
  modules::common::configs::vehicle_config_helper
  modules::common::vehicle_state::vehicle_state_provider
  modules::dreamview::backend::map::map_service
  modules::task_manager::common::task_manager_gflags
  modules::task_manager::proto::task_manager_cc_proto
  modules::task_manager::proto::task_manager_config_cc_proto
)
add_library(modules::task_manager::dead_end_routing_manager_lib  ALIAS   modules_task_manager_dead_end_routing_manager_lib)

add_library(modules_task_manager_task_manager_component_lib  SHARED
  task_manager_component.cc
)
set_target_properties(modules_task_manager_task_manager_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_task_manager_task_manager_component_lib
  modules::task_manager::cycle_routing_manager_lib
  modules::task_manager::parking_routing_manager_lib
  modules::task_manager::dead_end_routing_manager_lib
  cyber::cyber
  modules::task_manager::proto::task_manager_config_cc_proto
  modules::planning::proto::planning_cc_proto
)
add_library(modules::task_manager::task_manager_component_lib  ALIAS   modules_task_manager_task_manager_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libtask_manager_component  SHARED
  ${virtual_cc}
)
set_target_properties(libtask_manager_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libtask_manager_component
  modules::task_manager::task_manager_component_lib
)
