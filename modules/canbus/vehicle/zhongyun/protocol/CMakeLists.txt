cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_zhongyun_protocol)
message("${Green} [info] modules_canbus_vehicle_zhongyun_protocol cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_canbus_vehicle_zhongyun_protocol_canbus_zhongyun_protocol  SHARED
  ${virtual_cc}
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_canbus_zhongyun_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_canbus_zhongyun_protocol
  
)
add_library(modules::canbus::vehicle::zhongyun::protocol::canbus_zhongyun_protocol  ALIAS   modules_canbus_vehicle_zhongyun_protocol_canbus_zhongyun_protocol)

add_library(modules_canbus_vehicle_zhongyun_protocol_brake_control_a4  SHARED
  brake_control_a4.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_brake_control_a4  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_brake_control_a4
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::protocol::brake_control_a4  ALIAS   modules_canbus_vehicle_zhongyun_protocol_brake_control_a4)

add_library(modules_canbus_vehicle_zhongyun_protocol_enable_state_feedback_c3  SHARED
  enable_state_feedback_c3.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_enable_state_feedback_c3  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_enable_state_feedback_c3
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::protocol::enable_state_feedback_c3  ALIAS   modules_canbus_vehicle_zhongyun_protocol_enable_state_feedback_c3)

add_library(modules_canbus_vehicle_zhongyun_protocol_error_state_e1  SHARED
  error_state_e1.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_error_state_e1  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_error_state_e1
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::protocol::error_state_e1  ALIAS   modules_canbus_vehicle_zhongyun_protocol_error_state_e1)

add_library(modules_canbus_vehicle_zhongyun_protocol_gear_control_a1  SHARED
  gear_control_a1.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_gear_control_a1  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_gear_control_a1
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::protocol::gear_control_a1  ALIAS   modules_canbus_vehicle_zhongyun_protocol_gear_control_a1)

add_library(modules_canbus_vehicle_zhongyun_protocol_parking_control_a5  SHARED
  parking_control_a5.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_parking_control_a5  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_parking_control_a5
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::protocol::parking_control_a5  ALIAS   modules_canbus_vehicle_zhongyun_protocol_parking_control_a5)

add_library(modules_canbus_vehicle_zhongyun_protocol_steering_control_a2  SHARED
  steering_control_a2.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_steering_control_a2  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_steering_control_a2
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::protocol::steering_control_a2  ALIAS   modules_canbus_vehicle_zhongyun_protocol_steering_control_a2)

add_library(modules_canbus_vehicle_zhongyun_protocol_torque_control_a3  SHARED
  torque_control_a3.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_torque_control_a3  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_torque_control_a3
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::protocol::torque_control_a3  ALIAS   modules_canbus_vehicle_zhongyun_protocol_torque_control_a3)

add_library(modules_canbus_vehicle_zhongyun_protocol_vehicle_state_feedback_2_c4  SHARED
  vehicle_state_feedback_2_c4.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_vehicle_state_feedback_2_c4  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_vehicle_state_feedback_2_c4
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::protocol::vehicle_state_feedback_2_c4  ALIAS   modules_canbus_vehicle_zhongyun_protocol_vehicle_state_feedback_2_c4)

add_library(modules_canbus_vehicle_zhongyun_protocol_vehicle_state_feedback_c1  SHARED
  vehicle_state_feedback_c1.cc
)
set_target_properties(modules_canbus_vehicle_zhongyun_protocol_vehicle_state_feedback_c1  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_zhongyun_protocol_vehicle_state_feedback_c1
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::zhongyun::protocol::vehicle_state_feedback_c1  ALIAS   modules_canbus_vehicle_zhongyun_protocol_vehicle_state_feedback_c1)

