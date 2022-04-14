cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_transit)
message("${Green} [info] modules_canbus_vehicle_transit cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_transit_transit_vehicle_factory  SHARED
  transit_vehicle_factory.cc
)
set_target_properties(modules_canbus_vehicle_transit_transit_vehicle_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_transit_vehicle_factory
  modules::canbus::vehicle::transit::transit_controller
  modules::canbus::vehicle::transit::transit_message_manager
  modules::canbus::vehicle::abstract_vehicle_factory
)
add_library(modules::canbus::vehicle::transit::transit_vehicle_factory  ALIAS   modules_canbus_vehicle_transit_transit_vehicle_factory)

add_library(modules_canbus_vehicle_transit_transit_message_manager  SHARED
  transit_message_manager.cc
)
set_target_properties(modules_canbus_vehicle_transit_transit_message_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_transit_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::transit::protocol::canbus_transit_protocol
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::transit::transit_message_manager  ALIAS   modules_canbus_vehicle_transit_transit_message_manager)

add_library(modules_canbus_vehicle_transit_transit_controller  SHARED
  transit_controller.cc
)
set_target_properties(modules_canbus_vehicle_transit_transit_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_transit_controller
  modules::canbus::vehicle::transit::transit_message_manager
  modules::canbus::vehicle::vehicle_controller_base
  modules::common::kv_db::kv_db
  modules::common::proto::vehicle_signal_cc_proto
  modules::drivers::canbus::can_comm::can_sender
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::transit::transit_controller  ALIAS   modules_canbus_vehicle_transit_transit_controller)

