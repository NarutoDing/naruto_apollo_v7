cmake_minimum_required(VERSION 3.16)

project(modules_perception_onboard_common_flags)
message("${Green} [info] modules_perception_onboard_common_flags cmakelist ${ColourReset}")

add_library(modules_perception_onboard_common_flags_common_flags  SHARED
  common_flags.cc
)
set_target_properties(modules_perception_onboard_common_flags_common_flags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_common_flags_common_flags
  ${gflags_LIBRARIES}
)
add_library(modules::perception::onboard::common_flags::common_flags  ALIAS   modules_perception_onboard_common_flags_common_flags)

