cmake_minimum_required(VERSION 3.16)

project(modules_perception_onboard_inner_component_messages)
message("${Green} [info] modules_perception_onboard_inner_component_messages cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_onboard_inner_component_messages_inner_component_messages  SHARED
  ${virtual_cc}
  inner_component_messages.h
)
set_target_properties(modules_perception_onboard_inner_component_messages_inner_component_messages  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::onboard::inner_component_messages::inner_component_messages  ALIAS   modules_perception_onboard_inner_component_messages_inner_component_messages)

