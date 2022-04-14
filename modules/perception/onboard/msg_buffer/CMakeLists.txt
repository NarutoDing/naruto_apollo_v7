cmake_minimum_required(VERSION 3.16)

project(modules_perception_onboard_msg_buffer)
message("${Green} [info] modules_perception_onboard_msg_buffer cmakelist ${ColourReset}")

add_library(modules_perception_onboard_msg_buffer_msg_buffer  SHARED
  msg_buffer.cc
)
set_target_properties(modules_perception_onboard_msg_buffer_msg_buffer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_msg_buffer_msg_buffer
  cyber::cyber
  ${boost}
)
add_library(modules::perception::onboard::msg_buffer::msg_buffer  ALIAS   modules_perception_onboard_msg_buffer_msg_buffer)

