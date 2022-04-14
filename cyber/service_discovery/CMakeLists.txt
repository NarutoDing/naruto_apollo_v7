cmake_minimum_required(VERSION 3.16)

project(cyber_service_discovery)
message("${Green} [info] cyber_service_discovery cmakelist ${ColourReset}")

add_library(cyber_service_discovery_topology_manager  SHARED
  topology_manager.cc
)
set_target_properties(cyber_service_discovery_topology_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_topology_manager
  cyber::service_discovery::channel_manager
  cyber::service_discovery::node_manager
  cyber::service_discovery::service_manager
  cyber::service_discovery::communication::participant_listener
  cyber::transport::rtps::participant
)
add_library(cyber::service_discovery::topology_manager  ALIAS   cyber_service_discovery_topology_manager)

add_library(cyber_service_discovery_graph  SHARED
  container/graph.cc
)
set_target_properties(cyber_service_discovery_graph  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_graph
  cyber::base::atomic_rw_lock
)
add_library(cyber::service_discovery::graph  ALIAS   cyber_service_discovery_graph)

add_library(cyber_service_discovery_multi_value_warehouse  SHARED
  container/multi_value_warehouse.cc
)
set_target_properties(cyber_service_discovery_multi_value_warehouse  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_multi_value_warehouse
  cyber::service_discovery::warehouse_base
  cyber::base::atomic_rw_lock
)
add_library(cyber::service_discovery::multi_value_warehouse  ALIAS   cyber_service_discovery_multi_value_warehouse)

add_library(cyber_service_discovery_single_value_warehouse  SHARED
  container/single_value_warehouse.cc
)
set_target_properties(cyber_service_discovery_single_value_warehouse  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_single_value_warehouse
  cyber::service_discovery::warehouse_base
  cyber::base::atomic_rw_lock
)
add_library(cyber::service_discovery::single_value_warehouse  ALIAS   cyber_service_discovery_single_value_warehouse)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_service_discovery_warehouse_base  SHARED
  ${virtual_cc}
  container/warehouse_base.h
)
set_target_properties(cyber_service_discovery_warehouse_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_warehouse_base
  cyber::service_discovery::role
  
)
add_library(cyber::service_discovery::warehouse_base  ALIAS   cyber_service_discovery_warehouse_base)

add_library(cyber_service_discovery_role  SHARED
  role/role.cc
)
set_target_properties(cyber_service_discovery_role  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_role
  cyber::binary
  cyber::common::log
  cyber::common::types
  cyber::proto::role_attributes_cc_proto
)
add_library(cyber::service_discovery::role  ALIAS   cyber_service_discovery_role)

add_library(cyber_service_discovery_manager  SHARED
  specific_manager/manager.cc
)
set_target_properties(cyber_service_discovery_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_manager
  cyber::state
  cyber::base::signal
  cyber::message::message_traits
  cyber::message::protobuf_factory
  cyber::proto::proto_desc_cc_proto
  cyber::proto::role_attributes_cc_proto
  cyber::proto::topology_change_cc_proto
  cyber::service_discovery::communication::subscriber_listener
  cyber::time::time
  cyber::transport::qos::qos
  cyber::transport::rtps::attributes_filler
  cyber::transport::rtps::underlay_message_type
  ${fastrtps_LIB_DIR}/libfastrtps.so
)
add_library(cyber::service_discovery::manager  ALIAS   cyber_service_discovery_manager)

add_library(cyber_service_discovery_channel_manager  SHARED
  specific_manager/channel_manager.cc
)
set_target_properties(cyber_service_discovery_channel_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_channel_manager
  cyber::service_discovery::graph
  cyber::service_discovery::manager
  cyber::service_discovery::multi_value_warehouse
  cyber::service_discovery::single_value_warehouse
)
add_library(cyber::service_discovery::channel_manager  ALIAS   cyber_service_discovery_channel_manager)

add_library(cyber_service_discovery_node_manager  SHARED
  specific_manager/node_manager.cc
)
set_target_properties(cyber_service_discovery_node_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_node_manager
  cyber::service_discovery::manager
  cyber::service_discovery::multi_value_warehouse
  cyber::service_discovery::single_value_warehouse
)
add_library(cyber::service_discovery::node_manager  ALIAS   cyber_service_discovery_node_manager)

add_library(cyber_service_discovery_service_manager  SHARED
  specific_manager/service_manager.cc
)
set_target_properties(cyber_service_discovery_service_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_service_discovery_service_manager
  cyber::service_discovery::manager
  cyber::service_discovery::multi_value_warehouse
  cyber::service_discovery::single_value_warehouse
)
add_library(cyber::service_discovery::service_manager  ALIAS   cyber_service_discovery_service_manager)

