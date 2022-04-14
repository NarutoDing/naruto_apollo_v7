cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_motion_service)
message("${Green} [info] modules_perception_camera_lib_motion_service cmakelist ${ColourReset}")

add_library(modules_perception_camera_lib_motion_service_motion_service_lib  SHARED
  motion_service.cc
)
set_target_properties(modules_perception_camera_lib_motion_service_motion_service_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_motion_service_motion_service_lib
  cyber::cyber
  modules::common::math::math
  modules::drivers::proto::sensor_image_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::localization::proto::localization_status_cc_proto
  modules::localization::proto::pose_cc_proto
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::lib::motion::motion
  modules::perception::lib::registerer::registerer
  modules::perception::onboard::proto::motion_service_cc_proto
  modules::perception::proto::motion_service_cc_proto
)
add_library(modules::perception::camera::lib::motion_service::motion_service_lib  ALIAS   modules_perception_camera_lib_motion_service_motion_service_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libmotion_service  SHARED
  ${virtual_cc}
)
set_target_properties(libmotion_service  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libmotion_service
  modules::perception::camera::lib::motion_service::motion_service_lib
)
