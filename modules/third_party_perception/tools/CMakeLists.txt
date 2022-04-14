cmake_minimum_required(VERSION 3.16)

project(modules_third_party_perception_tools)
message("${Green} [info] modules_third_party_perception_tools cmakelist ${ColourReset}")

add_library(modules_third_party_perception_tools_third_party_perception_radar_conversion  SHARED
  conversion_radar.cc
)
set_target_properties(modules_third_party_perception_tools_third_party_perception_radar_conversion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_tools_third_party_perception_radar_conversion
  modules::canbus::proto::chassis_cc_proto
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::proto::drive_state_cc_proto
  modules::common::proto::vehicle_signal_cc_proto
  modules::drivers::canbus::proto::can_card_parameter_cc_proto
  modules::drivers::proto::conti_radar_cc_proto
  modules::drivers::proto::delphi_esr_cc_proto
  modules::drivers::radar::conti_radar::proto::conti_radar_conf_cc_proto
  modules::third_party_perception::common::third_party_perception_util
  modules::third_party_perception::proto::radar_obstacle_cc_proto
)
add_library(modules::third_party_perception::tools::third_party_perception_radar_conversion  ALIAS   modules_third_party_perception_tools_third_party_perception_radar_conversion)

add_library(modules_third_party_perception_tools_third_party_perception_smartereye_conversion  SHARED
  conversion_smartereye.cc
)
set_target_properties(modules_third_party_perception_tools_third_party_perception_smartereye_conversion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_tools_third_party_perception_smartereye_conversion
  modules::canbus::proto::chassis_cc_proto
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::proto::drive_state_cc_proto
  modules::common::proto::vehicle_signal_cc_proto
  modules::drivers::proto::smartereye_cc_proto
  modules::third_party_perception::common::third_party_perception_util
)
add_library(modules::third_party_perception::tools::third_party_perception_smartereye_conversion  ALIAS   modules_third_party_perception_tools_third_party_perception_smartereye_conversion)

add_library(modules_third_party_perception_tools_third_party_perception_mobileye_conversion  SHARED
  conversion_mobileye.cc
)
set_target_properties(modules_third_party_perception_tools_third_party_perception_mobileye_conversion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_tools_third_party_perception_mobileye_conversion
  modules::canbus::proto::chassis_cc_proto
  modules::common::configs::proto::vehicle_config_cc_proto
  modules::common::proto::drive_state_cc_proto
  modules::common::proto::vehicle_signal_cc_proto
  modules::drivers::proto::mobileye_cc_proto
  modules::drivers::proto::sensor_image_cc_proto
  modules::third_party_perception::common::third_party_perception_util
)
add_library(modules::third_party_perception::tools::third_party_perception_mobileye_conversion  ALIAS   modules_third_party_perception_tools_third_party_perception_mobileye_conversion)

add_library(modules_third_party_perception_tools_third_party_perception_fusion  SHARED
  fusion.cc
)
set_target_properties(modules_third_party_perception_tools_third_party_perception_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_tools_third_party_perception_fusion
  modules::common::math::geometry
  modules::perception::proto::perception_obstacle_cc_proto
  modules::third_party_perception::proto::third_party_perception_component_cc_proto
)
add_library(modules::third_party_perception::tools::third_party_perception_fusion  ALIAS   modules_third_party_perception_tools_third_party_perception_fusion)

add_library(modules_third_party_perception_tools_third_party_perception_filter  SHARED
  filter.cc
)
set_target_properties(modules_third_party_perception_tools_third_party_perception_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_tools_third_party_perception_filter
  modules::third_party_perception::common::third_party_perception_util
  modules::third_party_perception::proto::radar_obstacle_cc_proto
)
add_library(modules::third_party_perception::tools::third_party_perception_filter  ALIAS   modules_third_party_perception_tools_third_party_perception_filter)

