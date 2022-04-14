cmake_minimum_required(VERSION 3.16)

project(modules_canbus_vehicle)
message("${Green} [info] modules_canbus_vehicle cmakelist ${ColourReset}")

add_library(modules_canbus_vehicle_vehicle_controller_base  SHARED
  vehicle_controller.cc
)
set_target_properties(modules_canbus_vehicle_vehicle_controller_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_vehicle_controller_base
  modules::canbus::proto::canbus_conf_cc_proto
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::proto::vehicle_parameter_cc_proto
  modules::common::configs::vehicle_config_helper
  modules::common::proto::error_code_cc_proto
  modules::control::proto::control_cmd_cc_proto
  modules::drivers::canbus::can_client::can_client
  modules::drivers::canbus::can_comm::can_sender
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::vehicle_controller_base  ALIAS   modules_canbus_vehicle_vehicle_controller_base)

add_library(modules_canbus_vehicle_abstract_vehicle_factory  SHARED
  abstract_vehicle_factory.cc
)
set_target_properties(modules_canbus_vehicle_abstract_vehicle_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_abstract_vehicle_factory
  modules::canbus::proto::chassis_detail_cc_proto
  modules::canbus::vehicle::vehicle_controller_base
  modules::drivers::canbus::can_comm::message_manager_base
  modules::drivers::canbus::common::canbus_common
)
add_library(modules::canbus::vehicle::abstract_vehicle_factory  ALIAS   modules_canbus_vehicle_abstract_vehicle_factory)

add_library(modules_canbus_vehicle_vehicle_factory  SHARED
  vehicle_factory.cc
)
set_target_properties(modules_canbus_vehicle_vehicle_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_canbus_vehicle_vehicle_factory
  modules::canbus::vehicle::abstract_vehicle_factory
  modules::canbus::vehicle::ch::ch_vehicle_factory
  modules::canbus::vehicle::devkit::devkit_vehicle_factory
  modules::canbus::vehicle::ge3::ge3_vehicle_factory
  modules::canbus::vehicle::gem::gem_vehicle_factory
  modules::canbus::vehicle::lexus::lexus_vehicle_factory
  modules::canbus::vehicle::lincoln::lincoln_vehicle_factory
  modules::canbus::vehicle::neolix_edu::neolix_edu_vehicle_factory
  modules::canbus::vehicle::transit::transit_vehicle_factory
  modules::canbus::vehicle::wey::wey_vehicle_factory
  modules::canbus::vehicle::zhongyun::zhongyun_vehicle_factory
  modules::common::util::factory
)
add_library(modules::canbus::vehicle::vehicle_factory  ALIAS   modules_canbus_vehicle_vehicle_factory)

