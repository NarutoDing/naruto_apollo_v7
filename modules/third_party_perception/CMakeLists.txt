cmake_minimum_required(VERSION 3.16)

project(modules_third_party_perception)
message("${Green} [info] modules_third_party_perception cmakelist ${ColourReset}")

add_library(modules_third_party_perception_third_party_perception_lib  SHARED
  third_party_perception_base.cc
)
set_target_properties(modules_third_party_perception_third_party_perception_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_third_party_perception_lib
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::third_party_perception::tools::third_party_perception_filter
  modules::third_party_perception::tools::third_party_perception_fusion
  modules::third_party_perception::tools::third_party_perception_mobileye_conversion
  modules::third_party_perception::tools::third_party_perception_radar_conversion
  modules::third_party_perception::tools::third_party_perception_smartereye_conversion
)
add_library(modules::third_party_perception::third_party_perception_lib  ALIAS   modules_third_party_perception_third_party_perception_lib)

add_library(modules_third_party_perception_third_party_perception_mobileye_lib  SHARED
  third_party_perception_mobileye.cc
)
set_target_properties(modules_third_party_perception_third_party_perception_mobileye_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_third_party_perception_mobileye_lib
  modules::third_party_perception::third_party_perception_lib
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::third_party_perception::tools::third_party_perception_filter
  modules::third_party_perception::tools::third_party_perception_fusion
  modules::third_party_perception::tools::third_party_perception_mobileye_conversion
  modules::third_party_perception::tools::third_party_perception_radar_conversion
  modules::third_party_perception::tools::third_party_perception_smartereye_conversion
)
add_library(modules::third_party_perception::third_party_perception_mobileye_lib  ALIAS   modules_third_party_perception_third_party_perception_mobileye_lib)

add_library(modules_third_party_perception_third_party_perception_smartereye_lib  SHARED
  third_party_perception_smartereye.cc
)
set_target_properties(modules_third_party_perception_third_party_perception_smartereye_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_third_party_perception_smartereye_lib
  modules::third_party_perception::third_party_perception_lib
  cyber::cyber
  modules::common::adapters::adapter_gflags
  modules::common::util::message_util
  modules::third_party_perception::tools::third_party_perception_filter
  modules::third_party_perception::tools::third_party_perception_fusion
  modules::third_party_perception::tools::third_party_perception_mobileye_conversion
  modules::third_party_perception::tools::third_party_perception_radar_conversion
  modules::third_party_perception::tools::third_party_perception_smartereye_conversion
)
add_library(modules::third_party_perception::third_party_perception_smartereye_lib  ALIAS   modules_third_party_perception_third_party_perception_smartereye_lib)

add_library(modules_third_party_perception_third_party_perception_component_lib  SHARED
  third_party_perception_component.cc
)
set_target_properties(modules_third_party_perception_third_party_perception_component_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_third_party_perception_third_party_perception_component_lib
  modules::third_party_perception::third_party_perception_lib
  modules::third_party_perception::third_party_perception_mobileye_lib
  modules::third_party_perception::third_party_perception_smartereye_lib
)
add_library(modules::third_party_perception::third_party_perception_component_lib  ALIAS   modules_third_party_perception_third_party_perception_component_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libthird_party_perception_component  SHARED
  ${virtual_cc}
)
set_target_properties(libthird_party_perception_component  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libthird_party_perception_component
  modules::third_party_perception::third_party_perception_component_lib
)
