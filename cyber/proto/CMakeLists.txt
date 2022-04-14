cmake_minimum_required(VERSION 3.16)

project(cyber_proto)
message("${Green} [info] cyber_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/cyber/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(cyber_proto_topology_change_cc_proto  SHARED
  topology_change.pb.cc
)
set_target_properties(cyber_proto_topology_change_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_proto_topology_change_cc_proto
  cyber::proto::role_attributes_cc_proto
)
add_library(cyber::proto::topology_change_cc_proto  ALIAS   cyber_proto_topology_change_cc_proto)

add_library(cyber_proto_dag_conf_cc_proto  SHARED
  dag_conf.pb.cc
)
set_target_properties(cyber_proto_dag_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_proto_dag_conf_cc_proto
  cyber::proto::component_conf_cc_proto
)
add_library(cyber::proto::dag_conf_cc_proto  ALIAS   cyber_proto_dag_conf_cc_proto)

add_library(cyber_proto_proto_desc_cc_proto  SHARED
  proto_desc.pb.cc
)
set_target_properties(cyber_proto_proto_desc_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::proto_desc_cc_proto  ALIAS   cyber_proto_proto_desc_cc_proto)

add_library(cyber_proto_choreography_conf_cc_proto  SHARED
  choreography_conf.pb.cc
)
set_target_properties(cyber_proto_choreography_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::choreography_conf_cc_proto  ALIAS   cyber_proto_choreography_conf_cc_proto)

add_library(cyber_proto_record_cc_proto  SHARED
  record.pb.cc
)
set_target_properties(cyber_proto_record_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::record_cc_proto  ALIAS   cyber_proto_record_cc_proto)

add_library(cyber_proto_component_conf_cc_proto  SHARED
  component_conf.pb.cc
)
set_target_properties(cyber_proto_component_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_proto_component_conf_cc_proto
  cyber::proto::qos_profile_cc_proto
)
add_library(cyber::proto::component_conf_cc_proto  ALIAS   cyber_proto_component_conf_cc_proto)

add_library(cyber_proto_cyber_conf_cc_proto  SHARED
  cyber_conf.pb.cc
)
set_target_properties(cyber_proto_cyber_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_proto_cyber_conf_cc_proto
  cyber::proto::scheduler_conf_cc_proto
  cyber::proto::transport_conf_cc_proto
  cyber::proto::run_mode_conf_cc_proto
  cyber::proto::perf_conf_cc_proto
)
add_library(cyber::proto::cyber_conf_cc_proto  ALIAS   cyber_proto_cyber_conf_cc_proto)

add_library(cyber_proto_perf_conf_cc_proto  SHARED
  perf_conf.pb.cc
)
set_target_properties(cyber_proto_perf_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::perf_conf_cc_proto  ALIAS   cyber_proto_perf_conf_cc_proto)

add_library(cyber_proto_classic_conf_cc_proto  SHARED
  classic_conf.pb.cc
)
set_target_properties(cyber_proto_classic_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::classic_conf_cc_proto  ALIAS   cyber_proto_classic_conf_cc_proto)

add_library(cyber_proto_parameter_cc_proto  SHARED
  parameter.pb.cc
)
set_target_properties(cyber_proto_parameter_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::parameter_cc_proto  ALIAS   cyber_proto_parameter_cc_proto)

add_library(cyber_proto_unit_test_cc_proto  SHARED
  unit_test.pb.cc
)
set_target_properties(cyber_proto_unit_test_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::unit_test_cc_proto  ALIAS   cyber_proto_unit_test_cc_proto)

add_library(cyber_proto_scheduler_conf_cc_proto  SHARED
  scheduler_conf.pb.cc
)
set_target_properties(cyber_proto_scheduler_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_proto_scheduler_conf_cc_proto
  cyber::proto::classic_conf_cc_proto
  cyber::proto::choreography_conf_cc_proto
)
add_library(cyber::proto::scheduler_conf_cc_proto  ALIAS   cyber_proto_scheduler_conf_cc_proto)

add_library(cyber_proto_transport_conf_cc_proto  SHARED
  transport_conf.pb.cc
)
set_target_properties(cyber_proto_transport_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::transport_conf_cc_proto  ALIAS   cyber_proto_transport_conf_cc_proto)

add_library(cyber_proto_qos_profile_cc_proto  SHARED
  qos_profile.pb.cc
)
set_target_properties(cyber_proto_qos_profile_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::qos_profile_cc_proto  ALIAS   cyber_proto_qos_profile_cc_proto)

add_library(cyber_proto_run_mode_conf_cc_proto  SHARED
  run_mode_conf.pb.cc
)
set_target_properties(cyber_proto_run_mode_conf_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::run_mode_conf_cc_proto  ALIAS   cyber_proto_run_mode_conf_cc_proto)

add_library(cyber_proto_role_attributes_cc_proto  SHARED
  role_attributes.pb.cc
)
set_target_properties(cyber_proto_role_attributes_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_proto_role_attributes_cc_proto
  cyber::proto::qos_profile_cc_proto
)
add_library(cyber::proto::role_attributes_cc_proto  ALIAS   cyber_proto_role_attributes_cc_proto)

add_library(cyber_proto_clock_cc_proto  SHARED
  clock.pb.cc
)
set_target_properties(cyber_proto_clock_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::proto::clock_cc_proto  ALIAS   cyber_proto_clock_cc_proto)

