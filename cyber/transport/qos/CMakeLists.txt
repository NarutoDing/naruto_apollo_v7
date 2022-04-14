cmake_minimum_required(VERSION 3.16)

project(cyber_transport_qos)
message("${Green} [info] cyber_transport_qos cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_qos_qos  SHARED
  ${virtual_cc}
)
set_target_properties(cyber_transport_qos_qos  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_qos_qos
  cyber::transport::qos::qos_profile_conf
)
add_library(cyber::transport::qos::qos  ALIAS   cyber_transport_qos_qos)

add_library(cyber_transport_qos_qos_profile_conf  SHARED
  qos_profile_conf.cc
)
set_target_properties(cyber_transport_qos_qos_profile_conf  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_qos_qos_profile_conf
  cyber::proto::qos_profile_cc_proto
)
add_library(cyber::transport::qos::qos_profile_conf  ALIAS   cyber_transport_qos_qos_profile_conf)

