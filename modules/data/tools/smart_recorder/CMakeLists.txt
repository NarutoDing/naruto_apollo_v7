cmake_minimum_required(VERSION 3.16)

project(modules_data_tools_smart_recorder)
message("${Green} [info] modules_data_tools_smart_recorder cmakelist ${ColourReset}")

add_library(modules_data_tools_smart_recorder_post_record_processor  SHARED
  post_record_processor.cc
)
set_target_properties(modules_data_tools_smart_recorder_post_record_processor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_post_record_processor
  modules::data::tools::smart_recorder::channel_pool
  modules::data::tools::smart_recorder::record_processor
  cyber::record::record_reader
  cyber::record::record_viewer
)
add_library(modules::data::tools::smart_recorder::post_record_processor  ALIAS   modules_data_tools_smart_recorder_post_record_processor)

add_library(modules_data_tools_smart_recorder_realtime_record_processor  SHARED
  realtime_record_processor.cc
)
set_target_properties(modules_data_tools_smart_recorder_realtime_record_processor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_realtime_record_processor
  modules::data::tools::smart_recorder::channel_pool
  modules::data::tools::smart_recorder::record_processor
  cyber::cyber
  cyber::record::record_file_reader
  cyber::record::record_reader
  cyber::record::record_viewer
  cyber::tools::cyber_recorder::recorder
  modules::data::tools::smart_recorder::proto::smart_recorder_status_cc_proto
  modules::monitor::common::monitor_manager
)
add_library(modules::data::tools::smart_recorder::realtime_record_processor  ALIAS   modules_data_tools_smart_recorder_realtime_record_processor)

add_library(modules_data_tools_smart_recorder_record_processor  SHARED
  record_processor.cc
)
set_target_properties(modules_data_tools_smart_recorder_record_processor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_record_processor
  modules::data::tools::smart_recorder::drive_event_trigger
  modules::data::tools::smart_recorder::emergency_mode_trigger
  modules::data::tools::smart_recorder::hard_brake_trigger
  modules::data::tools::smart_recorder::interval_pool
  modules::data::tools::smart_recorder::regular_interval_trigger
  modules::data::tools::smart_recorder::small_topics_trigger
  modules::data::tools::smart_recorder::swerve_trigger
  cyber::common::file
  cyber::record::record_writer
  modules::common::util::util
)
add_library(modules::data::tools::smart_recorder::record_processor  ALIAS   modules_data_tools_smart_recorder_record_processor)

add_library(modules_data_tools_smart_recorder_smart_recorder_gflags  SHARED
  smart_recorder_gflags.cc
)
set_target_properties(modules_data_tools_smart_recorder_smart_recorder_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_smart_recorder_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::data::tools::smart_recorder::smart_recorder_gflags  ALIAS   modules_data_tools_smart_recorder_smart_recorder_gflags)

add_library(modules_data_tools_smart_recorder_drive_event_trigger  SHARED
  drive_event_trigger.cc
)
set_target_properties(modules_data_tools_smart_recorder_drive_event_trigger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_drive_event_trigger
  modules::data::tools::smart_recorder::trigger_base
  modules::common::adapters::adapter_gflags
  modules::common::proto::drive_event_cc_proto
)
add_library(modules::data::tools::smart_recorder::drive_event_trigger  ALIAS   modules_data_tools_smart_recorder_drive_event_trigger)

add_library(modules_data_tools_smart_recorder_emergency_mode_trigger  SHARED
  emergency_mode_trigger.cc
)
set_target_properties(modules_data_tools_smart_recorder_emergency_mode_trigger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_emergency_mode_trigger
  modules::data::tools::smart_recorder::trigger_base
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::control::proto::control_cmd_cc_proto
)
add_library(modules::data::tools::smart_recorder::emergency_mode_trigger  ALIAS   modules_data_tools_smart_recorder_emergency_mode_trigger)

add_library(modules_data_tools_smart_recorder_hard_brake_trigger  SHARED
  hard_brake_trigger.cc
)
set_target_properties(modules_data_tools_smart_recorder_hard_brake_trigger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_hard_brake_trigger
  modules::data::tools::smart_recorder::trigger_base
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::control::proto::control_cmd_cc_proto
)
add_library(modules::data::tools::smart_recorder::hard_brake_trigger  ALIAS   modules_data_tools_smart_recorder_hard_brake_trigger)

add_library(modules_data_tools_smart_recorder_small_topics_trigger  SHARED
  small_topics_trigger.cc
)
set_target_properties(modules_data_tools_smart_recorder_small_topics_trigger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_small_topics_trigger
  modules::data::tools::smart_recorder::channel_pool
  modules::data::tools::smart_recorder::trigger_base
)
add_library(modules::data::tools::smart_recorder::small_topics_trigger  ALIAS   modules_data_tools_smart_recorder_small_topics_trigger)

add_library(modules_data_tools_smart_recorder_swerve_trigger  SHARED
  swerve_trigger.cc
)
set_target_properties(modules_data_tools_smart_recorder_swerve_trigger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_swerve_trigger
  modules::data::tools::smart_recorder::trigger_base
  modules::canbus::proto::chassis_cc_proto
  modules::common::adapters::adapter_gflags
  modules::control::proto::control_cmd_cc_proto
)
add_library(modules::data::tools::smart_recorder::swerve_trigger  ALIAS   modules_data_tools_smart_recorder_swerve_trigger)

add_library(modules_data_tools_smart_recorder_regular_interval_trigger  SHARED
  regular_interval_trigger.cc
)
set_target_properties(modules_data_tools_smart_recorder_regular_interval_trigger  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_regular_interval_trigger
  modules::data::tools::smart_recorder::trigger_base
)
add_library(modules::data::tools::smart_recorder::regular_interval_trigger  ALIAS   modules_data_tools_smart_recorder_regular_interval_trigger)

add_library(modules_data_tools_smart_recorder_trigger_base  SHARED
  trigger_base.cc
)
set_target_properties(modules_data_tools_smart_recorder_trigger_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_trigger_base
  modules::data::tools::smart_recorder::interval_pool
  cyber::record::record_message
  modules::data::tools::smart_recorder::proto::smart_recorder_triggers_cc_proto
)
add_library(modules::data::tools::smart_recorder::trigger_base  ALIAS   modules_data_tools_smart_recorder_trigger_base)

add_library(modules_data_tools_smart_recorder_interval_pool  SHARED
  interval_pool.cc
)
set_target_properties(modules_data_tools_smart_recorder_interval_pool  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_interval_pool
  cyber::common::log
  cyber::common::macros
  ${absl}
)
add_library(modules::data::tools::smart_recorder::interval_pool  ALIAS   modules_data_tools_smart_recorder_interval_pool)

add_library(modules_data_tools_smart_recorder_channel_pool  SHARED
  channel_pool.cc
)
set_target_properties(modules_data_tools_smart_recorder_channel_pool  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_data_tools_smart_recorder_channel_pool
  cyber::common::macros
  modules::common::adapters::adapter_gflags
)
add_library(modules::data::tools::smart_recorder::channel_pool  ALIAS   modules_data_tools_smart_recorder_channel_pool)

add_executable(smart_recorder
  smart_recorder.cc
)
target_link_libraries(smart_recorder
  modules::data::tools::smart_recorder::post_record_processor
  modules::data::tools::smart_recorder::realtime_record_processor
  modules::data::tools::smart_recorder::smart_recorder_gflags
)
