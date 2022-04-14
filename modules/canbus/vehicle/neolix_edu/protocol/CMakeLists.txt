cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle_neolix_edu_protocol)
message("${Green} [info] modules_canbus_vehicle_neolix_edu_protocol cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_neolix_edu_protocol_canbus_neolix_edu_protocol  SHARED
  ads_brake_command_46.cc
  ads_diagnosis_628.cc
  ads_drive_command_50.cc
  ads_eps_command_56.cc
  ads_light_horn_command_310.cc
  aeb_diagnosis1_626.cc
  aeb_diagresp_718.cc
  aeb_frontwheelspeed_353.cc
  aeb_rearwheelspeed_354.cc
  aeb_systemstate_11.cc
  aeb_wheelimpulse_355.cc
  pas_1st_data_311.cc
  pas_2nd_data_312.cc
  vcu_brake_report_47.cc
  vcu_drive_report_52.cc
  vcu_eps_report_57.cc
  vcu_nm_401.cc
  vcu_powerstatus_214.cc
  vcu_vehicle_fault_response_201.cc
  vcu_vehicle_info_response_502.cc
  vcu_vehicle_status_report_101.cc
)
set_target_properties(modules_canbus_vehicle_neolix_edu_protocol_canbus_neolix_edu_protocol  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_neolix_edu_protocol_canbus_neolix_edu_protocol
  modules::canbus::proto::chassis_detail_cc_proto
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::neolix_edu::protocol::canbus_neolix_edu_protocol  ALIAS   modules_canbus_vehicle_neolix_edu_protocol_canbus_neolix_edu_protocol)

