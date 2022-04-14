cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_ch_protocol)
message("${Green} [info] modules_canbus_vehicle_ch_protocol cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_canbus_vehicle_ch_protocol_canbus_ch_protocol  SHARED
  ${virtual_cc}
)
set_target_properties(modules_canbus_vehicle_ch_protocol_canbus_ch_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_canbus_ch_protocol
  modules::canbus::vehicle::ch::protocol::brake_command_111
  modules::canbus::vehicle::ch::protocol::brake_status__511
  modules::canbus::vehicle::ch::protocol::control_command_115
  modules::canbus::vehicle::ch::protocol::ecu_status_1_515
  modules::canbus::vehicle::ch::protocol::ecu_status_2_516
  modules::canbus::vehicle::ch::protocol::ecu_status_3_517
  modules::canbus::vehicle::ch::protocol::gear_command_114
  modules::canbus::vehicle::ch::protocol::gear_status_514
  modules::canbus::vehicle::ch::protocol::steer_command_112
  modules::canbus::vehicle::ch::protocol::steer_status__512
  modules::canbus::vehicle::ch::protocol::throttle_command_110
  modules::canbus::vehicle::ch::protocol::throttle_status__510
  modules::canbus::vehicle::ch::protocol::turnsignal_command_113
  modules::canbus::vehicle::ch::protocol::turnsignal_status__513
)
add_library(modules::canbus::vehicle::ch::protocol::canbus_ch_protocol  ALIAS   modules_canbus_vehicle_ch_protocol_canbus_ch_protocol)

add_library(modules_canbus_vehicle_ch_protocol_brake_command_111  SHARED
  brake_command_111.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_brake_command_111  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_brake_command_111
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::brake_command_111  ALIAS   modules_canbus_vehicle_ch_protocol_brake_command_111)

add_library(modules_canbus_vehicle_ch_protocol_brake_status__511  SHARED
  brake_status__511.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_brake_status__511  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_brake_status__511
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::brake_status__511  ALIAS   modules_canbus_vehicle_ch_protocol_brake_status__511)

add_library(modules_canbus_vehicle_ch_protocol_control_command_115  SHARED
  control_command_115.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_control_command_115  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_control_command_115
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::control_command_115  ALIAS   modules_canbus_vehicle_ch_protocol_control_command_115)

add_library(modules_canbus_vehicle_ch_protocol_ecu_status_1_515  SHARED
  ecu_status_1_515.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_ecu_status_1_515  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_ecu_status_1_515
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::ecu_status_1_515  ALIAS   modules_canbus_vehicle_ch_protocol_ecu_status_1_515)

add_library(modules_canbus_vehicle_ch_protocol_ecu_status_2_516  SHARED
  ecu_status_2_516.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_ecu_status_2_516  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_ecu_status_2_516
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::ecu_status_2_516  ALIAS   modules_canbus_vehicle_ch_protocol_ecu_status_2_516)

add_library(modules_canbus_vehicle_ch_protocol_ecu_status_3_517  SHARED
  ecu_status_3_517.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_ecu_status_3_517  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_ecu_status_3_517
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::ecu_status_3_517  ALIAS   modules_canbus_vehicle_ch_protocol_ecu_status_3_517)

add_library(modules_canbus_vehicle_ch_protocol_gear_command_114  SHARED
  gear_command_114.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_gear_command_114  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_gear_command_114
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::gear_command_114  ALIAS   modules_canbus_vehicle_ch_protocol_gear_command_114)

add_library(modules_canbus_vehicle_ch_protocol_gear_status_514  SHARED
  gear_status_514.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_gear_status_514  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_gear_status_514
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::gear_status_514  ALIAS   modules_canbus_vehicle_ch_protocol_gear_status_514)

add_library(modules_canbus_vehicle_ch_protocol_steer_command_112  SHARED
  steer_command_112.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_steer_command_112  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_steer_command_112
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::steer_command_112  ALIAS   modules_canbus_vehicle_ch_protocol_steer_command_112)

add_library(modules_canbus_vehicle_ch_protocol_steer_status__512  SHARED
  steer_status__512.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_steer_status__512  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_steer_status__512
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::steer_status__512  ALIAS   modules_canbus_vehicle_ch_protocol_steer_status__512)

add_library(modules_canbus_vehicle_ch_protocol_throttle_command_110  SHARED
  throttle_command_110.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_throttle_command_110  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_throttle_command_110
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::throttle_command_110  ALIAS   modules_canbus_vehicle_ch_protocol_throttle_command_110)

add_library(modules_canbus_vehicle_ch_protocol_throttle_status__510  SHARED
  throttle_status__510.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_throttle_status__510  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_throttle_status__510
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::throttle_status__510  ALIAS   modules_canbus_vehicle_ch_protocol_throttle_status__510)

add_library(modules_canbus_vehicle_ch_protocol_turnsignal_command_113  SHARED
  turnsignal_command_113.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_turnsignal_command_113  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_turnsignal_command_113
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::turnsignal_command_113  ALIAS   modules_canbus_vehicle_ch_protocol_turnsignal_command_113)

add_library(modules_canbus_vehicle_ch_protocol_turnsignal_status__513  SHARED
  turnsignal_status__513.cc
)
set_target_properties(modules_canbus_vehicle_ch_protocol_turnsignal_status__513  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_ch_protocol_turnsignal_status__513
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::ch::protocol::turnsignal_status__513  ALIAS   modules_canbus_vehicle_ch_protocol_turnsignal_status__513)

