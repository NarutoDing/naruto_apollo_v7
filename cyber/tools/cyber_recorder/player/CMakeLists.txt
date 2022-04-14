cmake_minimum_required(VERSION 3.16)

project(cyber_tools_cyber_recorder_player)
message("${Green} [info] cyber_tools_cyber_recorder_player cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_tools_cyber_recorder_player_play_param  SHARED
  ${virtual_cc}
  play_param.h
)
set_target_properties(cyber_tools_cyber_recorder_player_play_param  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::tools::cyber_recorder::player::play_param  ALIAS   cyber_tools_cyber_recorder_player_play_param)

add_library(cyber_tools_cyber_recorder_player_play_task  SHARED
  play_task.cc
)
set_target_properties(cyber_tools_cyber_recorder_player_play_task  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_recorder_player_play_task
  cyber::common::log
  cyber::message::raw_message
  cyber::node::writer
)
add_library(cyber::tools::cyber_recorder::player::play_task  ALIAS   cyber_tools_cyber_recorder_player_play_task)

add_library(cyber_tools_cyber_recorder_player_play_task_buffer  SHARED
  play_task_buffer.cc
)
set_target_properties(cyber_tools_cyber_recorder_player_play_task_buffer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_recorder_player_play_task_buffer
  cyber::tools::cyber_recorder::player::play_task
)
add_library(cyber::tools::cyber_recorder::player::play_task_buffer  ALIAS   cyber_tools_cyber_recorder_player_play_task_buffer)

add_library(cyber_tools_cyber_recorder_player_play_task_consumer  SHARED
  play_task_consumer.cc
)
set_target_properties(cyber_tools_cyber_recorder_player_play_task_consumer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_recorder_player_play_task_consumer
  cyber::tools::cyber_recorder::player::play_task_buffer
  cyber::common::log
  cyber::time::time
)
add_library(cyber::tools::cyber_recorder::player::play_task_consumer  ALIAS   cyber_tools_cyber_recorder_player_play_task_consumer)

add_library(cyber_tools_cyber_recorder_player_play_task_producer  SHARED
  play_task_producer.cc
)
set_target_properties(cyber_tools_cyber_recorder_player_play_task_producer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_recorder_player_play_task_producer
  cyber::tools::cyber_recorder::player::play_param
  cyber::tools::cyber_recorder::player::play_task_buffer
  cyber::cyber
  cyber::common::log
  cyber::message::protobuf_factory
  cyber::message::raw_message
  cyber::node::node
  cyber::node::writer
  cyber::record::record_reader
  cyber::record::record_viewer
)
add_library(cyber::tools::cyber_recorder::player::play_task_producer  ALIAS   cyber_tools_cyber_recorder_player_play_task_producer)

add_library(cyber_tools_cyber_recorder_player_player  SHARED
  player.cc
)
set_target_properties(cyber_tools_cyber_recorder_player_player  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_tools_cyber_recorder_player_player
  cyber::tools::cyber_recorder::player::play_param
  cyber::tools::cyber_recorder::player::play_task_buffer
  cyber::tools::cyber_recorder::player::play_task_consumer
  cyber::tools::cyber_recorder::player::play_task_producer
  cyber::init
)
add_library(cyber::tools::cyber_recorder::player::player  ALIAS   cyber_tools_cyber_recorder_player_player)

