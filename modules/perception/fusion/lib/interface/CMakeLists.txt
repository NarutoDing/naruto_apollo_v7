cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_interface)
message("${Green} [info] modules_perception_fusion_lib_interface cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_fusion_lib_interface_interface  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_fusion_lib_interface_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_interface_interface
  cyber::common::macros
  modules::perception::fusion::base::base_forward_declaration
  modules::perception::fusion::base::sensor
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::fusion::lib::interface::interface  ALIAS   modules_perception_fusion_lib_interface_interface)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_fusion_lib_interface_base_multisensor_fusion  SHARED
  ${virtual_cc}
  base_multisensor_fusion.h
)
set_target_properties(modules_perception_fusion_lib_interface_base_multisensor_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_interface_base_multisensor_fusion
  cyber::common::macros
  modules::perception::fusion::base::base
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::fusion::lib::interface::base_multisensor_fusion  ALIAS   modules_perception_fusion_lib_interface_base_multisensor_fusion)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_fusion_lib_interface_base_fusion_system  SHARED
  ${virtual_cc}
  base_fusion_system.h
)
set_target_properties(modules_perception_fusion_lib_interface_base_fusion_system  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_interface_base_fusion_system
  cyber::common::macros
  modules::perception::base::frame
  modules::perception::fusion::base::base
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::fusion::lib::interface::base_fusion_system  ALIAS   modules_perception_fusion_lib_interface_base_fusion_system)

