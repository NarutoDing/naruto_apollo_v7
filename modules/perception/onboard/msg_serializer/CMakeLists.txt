cmake_minimum_required(VERSION 3.16)

project(modules_perception_onboard_msg_serializer)
message("${Green} [info] modules_perception_onboard_msg_serializer cmakelist ${ColourReset}")

add_library(modules_perception_onboard_msg_serializer_msg_serializer  SHARED
  msg_serializer.cc
)
set_target_properties(modules_perception_onboard_msg_serializer_msg_serializer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_msg_serializer_msg_serializer
  cyber::time::clock
  modules::perception::base::base
  modules::perception::onboard::common_flags::common_flags
  modules::perception::proto::perception_obstacle_cc_proto
  modules::prediction::proto::feature_cc_proto
  ${eigen}
)
add_library(modules::perception::onboard::msg_serializer::msg_serializer  ALIAS   modules_perception_onboard_msg_serializer_msg_serializer)

