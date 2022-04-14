cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_devkit_protocol)
message("${Green} [info] modules_canbus_vehicle_devkit_protocol cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_canbus_vehicle_devkit_protocol_canbus_devkit_protocol  SHARED
  ${virtual_cc}
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_canbus_devkit_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_canbus_devkit_protocol
  modules::canbus::vehicle::devkit::protocol::bms_report_512
  modules::canbus::vehicle::devkit::protocol::brake_command_101
  modules::canbus::vehicle::devkit::protocol::brake_report_501
  modules::canbus::vehicle::devkit::protocol::gear_command_103
  modules::canbus::vehicle::devkit::protocol::gear_report_503
  modules::canbus::vehicle::devkit::protocol::park_command_104
  modules::canbus::vehicle::devkit::protocol::park_report_504
  modules::canbus::vehicle::devkit::protocol::steering_command_102
  modules::canbus::vehicle::devkit::protocol::steering_report_502
  modules::canbus::vehicle::devkit::protocol::throttle_command_100
  modules::canbus::vehicle::devkit::protocol::throttle_report_500
  modules::canbus::vehicle::devkit::protocol::ultr_sensor_1_507
  modules::canbus::vehicle::devkit::protocol::ultr_sensor_2_508
  modules::canbus::vehicle::devkit::protocol::ultr_sensor_3_509
  modules::canbus::vehicle::devkit::protocol::ultr_sensor_4_510
  modules::canbus::vehicle::devkit::protocol::ultr_sensor_5_511
  modules::canbus::vehicle::devkit::protocol::vcu_report_505
  modules::canbus::vehicle::devkit::protocol::wheelspeed_report_506
)
add_library(modules::canbus::vehicle::devkit::protocol::canbus_devkit_protocol  ALIAS   modules_canbus_vehicle_devkit_protocol_canbus_devkit_protocol)

add_library(modules_canbus_vehicle_devkit_protocol_bms_report_512  SHARED
  bms_report_512.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_bms_report_512  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_bms_report_512
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::bms_report_512  ALIAS   modules_canbus_vehicle_devkit_protocol_bms_report_512)

add_library(modules_canbus_vehicle_devkit_protocol_brake_command_101  SHARED
  brake_command_101.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_brake_command_101  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_brake_command_101
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::brake_command_101  ALIAS   modules_canbus_vehicle_devkit_protocol_brake_command_101)

add_library(modules_canbus_vehicle_devkit_protocol_brake_report_501  SHARED
  brake_report_501.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_brake_report_501  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_brake_report_501
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::brake_report_501  ALIAS   modules_canbus_vehicle_devkit_protocol_brake_report_501)

add_library(modules_canbus_vehicle_devkit_protocol_gear_command_103  SHARED
  gear_command_103.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_gear_command_103  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_gear_command_103
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::gear_command_103  ALIAS   modules_canbus_vehicle_devkit_protocol_gear_command_103)

add_library(modules_canbus_vehicle_devkit_protocol_gear_report_503  SHARED
  gear_report_503.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_gear_report_503  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_gear_report_503
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::gear_report_503  ALIAS   modules_canbus_vehicle_devkit_protocol_gear_report_503)

add_library(modules_canbus_vehicle_devkit_protocol_park_command_104  SHARED
  park_command_104.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_park_command_104  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_park_command_104
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::park_command_104  ALIAS   modules_canbus_vehicle_devkit_protocol_park_command_104)

add_library(modules_canbus_vehicle_devkit_protocol_park_report_504  SHARED
  park_report_504.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_park_report_504  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_park_report_504
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::park_report_504  ALIAS   modules_canbus_vehicle_devkit_protocol_park_report_504)

add_library(modules_canbus_vehicle_devkit_protocol_steering_command_102  SHARED
  steering_command_102.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_steering_command_102  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_steering_command_102
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::steering_command_102  ALIAS   modules_canbus_vehicle_devkit_protocol_steering_command_102)

add_library(modules_canbus_vehicle_devkit_protocol_steering_report_502  SHARED
  steering_report_502.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_steering_report_502  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_steering_report_502
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::steering_report_502  ALIAS   modules_canbus_vehicle_devkit_protocol_steering_report_502)

add_library(modules_canbus_vehicle_devkit_protocol_throttle_command_100  SHARED
  throttle_command_100.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_throttle_command_100  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_throttle_command_100
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::throttle_command_100  ALIAS   modules_canbus_vehicle_devkit_protocol_throttle_command_100)

add_library(modules_canbus_vehicle_devkit_protocol_throttle_report_500  SHARED
  throttle_report_500.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_throttle_report_500  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_throttle_report_500
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::throttle_report_500  ALIAS   modules_canbus_vehicle_devkit_protocol_throttle_report_500)

add_library(modules_canbus_vehicle_devkit_protocol_ultr_sensor_1_507  SHARED
  ultr_sensor_1_507.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_ultr_sensor_1_507  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_ultr_sensor_1_507
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::ultr_sensor_1_507  ALIAS   modules_canbus_vehicle_devkit_protocol_ultr_sensor_1_507)

add_library(modules_canbus_vehicle_devkit_protocol_ultr_sensor_2_508  SHARED
  ultr_sensor_2_508.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_ultr_sensor_2_508  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_ultr_sensor_2_508
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::ultr_sensor_2_508  ALIAS   modules_canbus_vehicle_devkit_protocol_ultr_sensor_2_508)

add_library(modules_canbus_vehicle_devkit_protocol_ultr_sensor_3_509  SHARED
  ultr_sensor_3_509.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_ultr_sensor_3_509  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_ultr_sensor_3_509
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::ultr_sensor_3_509  ALIAS   modules_canbus_vehicle_devkit_protocol_ultr_sensor_3_509)

add_library(modules_canbus_vehicle_devkit_protocol_ultr_sensor_4_510  SHARED
  ultr_sensor_4_510.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_ultr_sensor_4_510  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_ultr_sensor_4_510
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::ultr_sensor_4_510  ALIAS   modules_canbus_vehicle_devkit_protocol_ultr_sensor_4_510)

add_library(modules_canbus_vehicle_devkit_protocol_ultr_sensor_5_511  SHARED
  ultr_sensor_5_511.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_ultr_sensor_5_511  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_ultr_sensor_5_511
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::ultr_sensor_5_511  ALIAS   modules_canbus_vehicle_devkit_protocol_ultr_sensor_5_511)

add_library(modules_canbus_vehicle_devkit_protocol_vcu_report_505  SHARED
  vcu_report_505.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_vcu_report_505  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_vcu_report_505
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::vcu_report_505  ALIAS   modules_canbus_vehicle_devkit_protocol_vcu_report_505)

add_library(modules_canbus_vehicle_devkit_protocol_wheelspeed_report_506  SHARED
  wheelspeed_report_506.cc
)
set_target_properties(modules_canbus_vehicle_devkit_protocol_wheelspeed_report_506  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_devkit_protocol_wheelspeed_report_506
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::devkit::protocol::wheelspeed_report_506  ALIAS   modules_canbus_vehicle_devkit_protocol_wheelspeed_report_506)

