cmake_minimum_required(VERSION 3.16)

project(cyber_node)
message("${Green} [info] cyber_node cmakelist ${ColourReset}")

add_library(cyber_node_node  SHARED
  node.cc
)
set_target_properties(cyber_node_node  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_node_node
  cyber::node::node_channel_impl
  cyber::node::node_service_impl
)
add_library(cyber::node::node  ALIAS   cyber_node_node)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_node_node_channel_impl  SHARED
  ${virtual_cc}
  node_channel_impl.h
)
set_target_properties(cyber_node_node_channel_impl  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_node_node_channel_impl
  cyber::node::reader
  cyber::node::writer
  cyber::blocker::intra_reader
  cyber::blocker::intra_writer
  cyber::common::global_data
  cyber::message::message_traits
  cyber::proto::run_mode_conf_cc_proto
)
add_library(cyber::node::node_channel_impl  ALIAS   cyber_node_node_channel_impl)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_node_node_service_impl  SHARED
  ${virtual_cc}
  node_service_impl.h
)
set_target_properties(cyber_node_node_service_impl  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_node_node_service_impl
  cyber::node::reader
  cyber::node::writer
  cyber::common::global_data
  cyber::service::service
  cyber::service::client
  cyber::service_discovery::topology_manager
)
add_library(cyber::node::node_service_impl  ALIAS   cyber_node_node_service_impl)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_node_reader  SHARED
  ${virtual_cc}
  reader.h
)
set_target_properties(cyber_node_reader  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_node_reader
  cyber::node::reader_base
  cyber::blocker::blocker
  cyber::common::global_data
  cyber::croutine::routine_factory
  cyber::data::data_visitor
  cyber::proto::topology_change_cc_proto
  cyber::scheduler::scheduler
  cyber::service_discovery::topology_manager
  cyber::time::time
  cyber::transport::transport
)
add_library(cyber::node::reader  ALIAS   cyber_node_reader)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_node_reader_base  SHARED
  ${virtual_cc}
  reader_base.h
)
set_target_properties(cyber_node_reader_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_node_reader_base
  cyber::event::perf_event_cache
  cyber::transport::transport
)
add_library(cyber::node::reader_base  ALIAS   cyber_node_reader_base)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_node_writer  SHARED
  ${virtual_cc}
  writer.h
)
set_target_properties(cyber_node_writer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_node_writer
  cyber::node::writer_base
  cyber::common::log
  cyber::proto::topology_change_cc_proto
  cyber::service_discovery::topology_manager
  cyber::transport::transport
)
add_library(cyber::node::writer  ALIAS   cyber_node_writer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_node_writer_base  SHARED
  ${virtual_cc}
  writer_base.h
)
set_target_properties(cyber_node_writer_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_node_writer_base
  cyber::common::macros
  cyber::common::util
  cyber::proto::role_attributes_cc_proto
)
add_library(cyber::node::writer_base  ALIAS   cyber_node_writer_base)

