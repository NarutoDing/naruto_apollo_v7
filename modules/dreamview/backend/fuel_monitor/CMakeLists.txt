cmake_minimum_required(VERSION 3.16)

project(modules_dreamview_backend_fuel_monitor)
message("${Green} [info] modules_dreamview_backend_fuel_monitor cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_dreamview_backend_fuel_monitor_fuel_monitor  SHARED
  ${virtual_cc}
  fuel_monitor.h
)
set_target_properties(modules_dreamview_backend_fuel_monitor_fuel_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_fuel_monitor_fuel_monitor
  ${json}
)
add_library(modules::dreamview::backend::fuel_monitor::fuel_monitor  ALIAS   modules_dreamview_backend_fuel_monitor_fuel_monitor)

add_library(modules_dreamview_backend_fuel_monitor_data_collection_monitor  SHARED
  data_collection_monitor.cc
)
set_target_properties(modules_dreamview_backend_fuel_monitor_data_collection_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_fuel_monitor_data_collection_monitor
  modules::dreamview::backend::fuel_monitor::fuel_monitor
  modules::dreamview::backend::fuel_monitor::fuel_monitor_gflags
  cyber::cyber
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::configs::vehicle_config_helper
  modules::dreamview::backend::common::dreamview_gflags
  modules::dreamview::backend::hmi::vehicle_manager
  modules::dreamview::proto::data_collection_table_cc_proto
  ${gflags_LIBRARIES}
  ${json}
  
)
add_library(modules::dreamview::backend::fuel_monitor::data_collection_monitor  ALIAS   modules_dreamview_backend_fuel_monitor_data_collection_monitor)

add_library(modules_dreamview_backend_fuel_monitor_preprocess_monitor  SHARED
  preprocess_monitor.cc
)
set_target_properties(modules_dreamview_backend_fuel_monitor_preprocess_monitor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_fuel_monitor_preprocess_monitor
  modules::dreamview::backend::fuel_monitor::fuel_monitor
  modules::dreamview::backend::fuel_monitor::fuel_monitor_gflags
  cyber::cyber
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::common::configs::vehicle_config_helper
  modules::dreamview::backend::common::dreamview_gflags
  modules::dreamview::backend::hmi::vehicle_manager
  modules::dreamview::proto::preprocess_table_cc_proto
  ${gflags_LIBRARIES}
  ${json}
  ${absl}
)
add_library(modules::dreamview::backend::fuel_monitor::preprocess_monitor  ALIAS   modules_dreamview_backend_fuel_monitor_preprocess_monitor)

add_library(modules_dreamview_backend_fuel_monitor_fuel_monitor_gflags  SHARED
  fuel_monitor_gflags.cc
)
set_target_properties(modules_dreamview_backend_fuel_monitor_fuel_monitor_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_fuel_monitor_fuel_monitor_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::dreamview::backend::fuel_monitor::fuel_monitor_gflags  ALIAS   modules_dreamview_backend_fuel_monitor_fuel_monitor_gflags)

add_library(modules_dreamview_backend_fuel_monitor_fuel_monitor_manager  SHARED
  fuel_monitor_manager.cc
)
set_target_properties(modules_dreamview_backend_fuel_monitor_fuel_monitor_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_dreamview_backend_fuel_monitor_fuel_monitor_manager
  modules::dreamview::backend::fuel_monitor::fuel_monitor
  cyber::common::log
  cyber::common::macros
  modules::common::util::future
  ${boost}
)
add_library(modules::dreamview::backend::fuel_monitor::fuel_monitor_manager  ALIAS   modules_dreamview_backend_fuel_monitor_fuel_monitor_manager)

