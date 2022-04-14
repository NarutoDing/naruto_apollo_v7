cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_transit_protocol)
message("${Green} [info] modules_canbus_vehicle_transit_protocol cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_canbus_vehicle_transit_protocol_canbus_transit_protocol  SHARED
  ${virtual_cc}
)
set_target_properties(modules_canbus_vehicle_transit_protocol_canbus_transit_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_canbus_transit_protocol
  modules::canbus::vehicle::transit::protocol::adc_auxiliarycontrol_110
  modules::canbus::vehicle::transit::protocol::adc_motioncontrol1_10
  modules::canbus::vehicle::transit::protocol::adc_motioncontrollimits1_12
  modules::canbus::vehicle::transit::protocol::llc_auxiliaryfeedback_120
  modules::canbus::vehicle::transit::protocol::llc_diag_brakecontrol_721
  modules::canbus::vehicle::transit::protocol::llc_diag_fault_620
  modules::canbus::vehicle::transit::protocol::llc_diag_steeringcontrol_722
  modules::canbus::vehicle::transit::protocol::llc_motioncommandfeedback1_22
  modules::canbus::vehicle::transit::protocol::llc_motionfeedback1_20
  modules::canbus::vehicle::transit::protocol::llc_motionfeedback2_21
  modules::canbus::vehicle::transit::protocol::llc_vehiclelimits_24
  modules::canbus::vehicle::transit::protocol::llc_vehiclestatus_25
)
add_library(modules::canbus::vehicle::transit::protocol::canbus_transit_protocol  ALIAS   modules_canbus_vehicle_transit_protocol_canbus_transit_protocol)

add_library(modules_canbus_vehicle_transit_protocol_adc_auxiliarycontrol_110  SHARED
  adc_auxiliarycontrol_110.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_adc_auxiliarycontrol_110  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_adc_auxiliarycontrol_110
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::adc_auxiliarycontrol_110  ALIAS   modules_canbus_vehicle_transit_protocol_adc_auxiliarycontrol_110)

add_library(modules_canbus_vehicle_transit_protocol_adc_motioncontrol1_10  SHARED
  adc_motioncontrol1_10.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_adc_motioncontrol1_10  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_adc_motioncontrol1_10
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::adc_motioncontrol1_10  ALIAS   modules_canbus_vehicle_transit_protocol_adc_motioncontrol1_10)

add_library(modules_canbus_vehicle_transit_protocol_adc_motioncontrollimits1_12  SHARED
  adc_motioncontrollimits1_12.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_adc_motioncontrollimits1_12  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_adc_motioncontrollimits1_12
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::adc_motioncontrollimits1_12  ALIAS   modules_canbus_vehicle_transit_protocol_adc_motioncontrollimits1_12)

add_library(modules_canbus_vehicle_transit_protocol_llc_auxiliaryfeedback_120  SHARED
  llc_auxiliaryfeedback_120.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_llc_auxiliaryfeedback_120  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_llc_auxiliaryfeedback_120
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::llc_auxiliaryfeedback_120  ALIAS   modules_canbus_vehicle_transit_protocol_llc_auxiliaryfeedback_120)

add_library(modules_canbus_vehicle_transit_protocol_llc_diag_brakecontrol_721  SHARED
  llc_diag_brakecontrol_721.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_llc_diag_brakecontrol_721  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_llc_diag_brakecontrol_721
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::llc_diag_brakecontrol_721  ALIAS   modules_canbus_vehicle_transit_protocol_llc_diag_brakecontrol_721)

add_library(modules_canbus_vehicle_transit_protocol_llc_diag_fault_620  SHARED
  llc_diag_fault_620.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_llc_diag_fault_620  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_llc_diag_fault_620
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::llc_diag_fault_620  ALIAS   modules_canbus_vehicle_transit_protocol_llc_diag_fault_620)

add_library(modules_canbus_vehicle_transit_protocol_llc_diag_steeringcontrol_722  SHARED
  llc_diag_steeringcontrol_722.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_llc_diag_steeringcontrol_722  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_llc_diag_steeringcontrol_722
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::llc_diag_steeringcontrol_722  ALIAS   modules_canbus_vehicle_transit_protocol_llc_diag_steeringcontrol_722)

add_library(modules_canbus_vehicle_transit_protocol_llc_motioncommandfeedback1_22  SHARED
  llc_motioncommandfeedback1_22.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_llc_motioncommandfeedback1_22  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_llc_motioncommandfeedback1_22
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::llc_motioncommandfeedback1_22  ALIAS   modules_canbus_vehicle_transit_protocol_llc_motioncommandfeedback1_22)

add_library(modules_canbus_vehicle_transit_protocol_llc_motionfeedback1_20  SHARED
  llc_motionfeedback1_20.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_llc_motionfeedback1_20  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_llc_motionfeedback1_20
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::llc_motionfeedback1_20  ALIAS   modules_canbus_vehicle_transit_protocol_llc_motionfeedback1_20)

add_library(modules_canbus_vehicle_transit_protocol_llc_motionfeedback2_21  SHARED
  llc_motionfeedback2_21.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_llc_motionfeedback2_21  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_llc_motionfeedback2_21
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::llc_motionfeedback2_21  ALIAS   modules_canbus_vehicle_transit_protocol_llc_motionfeedback2_21)

add_library(modules_canbus_vehicle_transit_protocol_llc_vehiclelimits_24  SHARED
  llc_vehiclelimits_24.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_llc_vehiclelimits_24  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_llc_vehiclelimits_24
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::llc_vehiclelimits_24  ALIAS   modules_canbus_vehicle_transit_protocol_llc_vehiclelimits_24)

add_library(modules_canbus_vehicle_transit_protocol_llc_vehiclestatus_25  SHARED
  llc_vehiclestatus_25.cc
)
set_target_properties(modules_canbus_vehicle_transit_protocol_llc_vehiclestatus_25  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_transit_protocol_llc_vehiclestatus_25
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
  
)
add_library(modules::canbus::vehicle::transit::protocol::llc_vehiclestatus_25  ALIAS   modules_canbus_vehicle_transit_protocol_llc_vehiclestatus_25)

