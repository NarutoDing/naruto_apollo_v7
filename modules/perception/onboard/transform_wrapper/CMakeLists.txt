cmake_minimum_required(VERSION 3.16)

project(modules_perception_onboard_transform_wrapper)
message("${Green} [info] modules_perception_onboard_transform_wrapper cmakelist ${ColourReset}")

add_library(modules_perception_onboard_transform_wrapper_transform_wrapper  SHARED
  transform_wrapper.cc
)
set_target_properties(modules_perception_onboard_transform_wrapper_transform_wrapper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_onboard_transform_wrapper_transform_wrapper
  modules::common::util::string_util
  modules::perception::common::sensor_manager::sensor_manager
  modules::transform::buffer
  ${gflags_LIBRARIES}
  ${eigen}
)
add_library(modules::perception::onboard::transform_wrapper::transform_wrapper  ALIAS   modules_perception_onboard_transform_wrapper_transform_wrapper)

