cmake_minimum_required(VERSION 3.16)

project(modules_drivers_proto)
message("${Green} [info] modules_drivers_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/drivers/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_drivers_proto_delphi_esr_cc_proto  SHARED
  delphi_esr.pb.cc
)
set_target_properties(modules_drivers_proto_delphi_esr_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_proto_delphi_esr_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::proto::delphi_esr_cc_proto  ALIAS   modules_drivers_proto_delphi_esr_cc_proto)

add_library(modules_drivers_proto_sensor_image_cc_proto  SHARED
  sensor_image.pb.cc
)
set_target_properties(modules_drivers_proto_sensor_image_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_proto_sensor_image_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::proto::sensor_image_cc_proto  ALIAS   modules_drivers_proto_sensor_image_cc_proto)

add_library(modules_drivers_proto_mobileye_cc_proto  SHARED
  mobileye.pb.cc
)
set_target_properties(modules_drivers_proto_mobileye_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_proto_mobileye_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::proto::mobileye_cc_proto  ALIAS   modules_drivers_proto_mobileye_cc_proto)

add_library(modules_drivers_proto_ultrasonic_radar_cc_proto  SHARED
  ultrasonic_radar.pb.cc
)
set_target_properties(modules_drivers_proto_ultrasonic_radar_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_proto_ultrasonic_radar_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::proto::ultrasonic_radar_cc_proto  ALIAS   modules_drivers_proto_ultrasonic_radar_cc_proto)

add_library(modules_drivers_proto_racobit_radar_cc_proto  SHARED
  racobit_radar.pb.cc
)
set_target_properties(modules_drivers_proto_racobit_radar_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_proto_racobit_radar_cc_proto
  modules::common::proto::header_cc_proto
  modules::drivers::radar::racobit_radar::proto::racobit_radar_conf_cc_proto
)
add_library(modules::drivers::proto::racobit_radar_cc_proto  ALIAS   modules_drivers_proto_racobit_radar_cc_proto)

add_library(modules_drivers_proto_conti_radar_cc_proto  SHARED
  conti_radar.pb.cc
)
set_target_properties(modules_drivers_proto_conti_radar_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_proto_conti_radar_cc_proto
  modules::common::proto::header_cc_proto
  modules::drivers::radar::conti_radar::proto::conti_radar_conf_cc_proto
)
add_library(modules::drivers::proto::conti_radar_cc_proto  ALIAS   modules_drivers_proto_conti_radar_cc_proto)

add_library(modules_drivers_proto_smartereye_cc_proto  SHARED
  smartereye.pb.cc
)
set_target_properties(modules_drivers_proto_smartereye_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_proto_smartereye_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::proto::smartereye_cc_proto  ALIAS   modules_drivers_proto_smartereye_cc_proto)

add_library(modules_drivers_proto_pointcloud_cc_proto  SHARED
  pointcloud.pb.cc
)
set_target_properties(modules_drivers_proto_pointcloud_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_proto_pointcloud_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::proto::pointcloud_cc_proto  ALIAS   modules_drivers_proto_pointcloud_cc_proto)

add_library(modules_drivers_proto_radar_cc_proto  SHARED
  radar.pb.cc
)
set_target_properties(modules_drivers_proto_radar_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_proto_radar_cc_proto
  modules::common::proto::error_code_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::proto::radar_cc_proto  ALIAS   modules_drivers_proto_radar_cc_proto)

