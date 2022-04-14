cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_zhongyun)
message("${Green} [info] modules_canbus_vehicle_zhongyun cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_zhongyun_zhongyun_vehicle_factory  SHARED
  zhongyun_vehicle_factory.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_zhongyun_vehicle_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_zhongyun_vehicle_factory
  modules::canbus::vehicle::zhongyun::zhongyun_controller
  modules::canbus::vehicle::zhongyun::zhongyun_message_manager
  modules::canbus::vehicle::abstract_vehicle_factory
)
add_library(modules::canbus::vehicle::zhongyun::zhongyun_vehicle_factory  ALIAS   modules_canbus_vehicle_zhongyun_zhongyun_vehicle_factory)

add_library(modules_canbus_vehicle_zhongyun_zhongyun_message_manager  SHARED
  zhongyun_message_manager.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_zhongyun_message_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_zhongyun_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::zhongyun::protocol::canbus_zhongyun_protocol
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::zhongyun_message_manager  ALIAS   modules_canbus_vehicle_zhongyun_zhongyun_message_manager)

add_library(modules_canbus_vehicle_zhongyun_zhongyun_controller  SHARED
  zhongyun_controller.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_zhongyun_controller  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_zhongyun_controller
  modules::canbus::vehicle::zhongyun::zhongyun_message_manager
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::vehicle_controller_base
  modules::canbus::vehicle::zhongyun::protocol::canbus_zhongyun_protocol
  modules::drivers::canbus::can_comm::can_sender
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::zhongyun_controller  ALIAS   modules_canbus_vehicle_zhongyun_zhongyun_controller)

