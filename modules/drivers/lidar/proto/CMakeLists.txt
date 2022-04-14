cmake_minimum_required(VERSION 3.16)

project(modules_drivers_lidar_proto)
message("${Green} [info] modules_drivers_lidar_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/drivers/lidar/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_drivers_lidar_proto_velodyne_cc_proto  SHARED
  velodyne.pb.cc
)
set_target_properties(modules_drivers_lidar_proto_velodyne_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_proto_velodyne_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::lidar::proto::velodyne_cc_proto  ALIAS   modules_drivers_lidar_proto_velodyne_cc_proto)

add_library(modules_drivers_lidar_proto_velodyne_config_cc_proto  SHARED
  velodyne_config.pb.cc
)
set_target_properties(modules_drivers_lidar_proto_velodyne_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_proto_velodyne_config_cc_proto
  modules::drivers::lidar::proto::velodyne_cc_proto
)
add_library(modules::drivers::lidar::proto::velodyne_config_cc_proto  ALIAS   modules_drivers_lidar_proto_velodyne_config_cc_proto)

add_library(modules_drivers_lidar_proto_hesai_cc_proto  SHARED
  hesai.pb.cc
)
set_target_properties(modules_drivers_lidar_proto_hesai_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_proto_hesai_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::lidar::proto::hesai_cc_proto  ALIAS   modules_drivers_lidar_proto_hesai_cc_proto)

add_library(modules_drivers_lidar_proto_hesai_config_cc_proto  SHARED
  hesai_config.pb.cc
)
set_target_properties(modules_drivers_lidar_proto_hesai_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_proto_hesai_config_cc_proto
  modules::drivers::lidar::proto::hesai_cc_proto
)
add_library(modules::drivers::lidar::proto::hesai_config_cc_proto  ALIAS   modules_drivers_lidar_proto_hesai_config_cc_proto)

add_library(modules_drivers_lidar_proto_robosense_cc_proto  SHARED
  robosense.pb.cc
  robosense_config.pb.cc
)
set_target_properties(modules_drivers_lidar_proto_robosense_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_proto_robosense_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::lidar::proto::robosense_cc_proto  ALIAS   modules_drivers_lidar_proto_robosense_cc_proto)

add_library(modules_drivers_lidar_proto_lidar_parameter_cc_proto  SHARED
  lidar_parameter.pb.cc
)
set_target_properties(modules_drivers_lidar_proto_lidar_parameter_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::drivers::lidar::proto::lidar_parameter_cc_proto  ALIAS   modules_drivers_lidar_proto_lidar_parameter_cc_proto)

add_library(modules_drivers_lidar_proto_config_cc_proto  SHARED
  config.pb.cc
)
set_target_properties(modules_drivers_lidar_proto_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_drivers_lidar_proto_config_cc_proto
  modules::drivers::lidar::proto::hesai_config_cc_proto
  modules::drivers::lidar::proto::lidar_parameter_cc_proto
  modules::drivers::lidar::proto::robosense_cc_proto
  modules::drivers::lidar::proto::velodyne_config_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::drivers::lidar::proto::config_cc_proto  ALIAS   modules_drivers_lidar_proto_config_cc_proto)

