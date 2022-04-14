cmake_minimum_required(VERSION 3.16)

project(cyber_transport_common)
message("${Green} [info] cyber_transport_common cmakelist ${ColourReset}")

add_library(cyber_transport_common_endpoint  SHARED
  endpoint.cc
)
set_target_properties(cyber_transport_common_endpoint  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_common_endpoint
  cyber::transport::common::identity
  cyber::common::global_data
  cyber::proto::role_attributes_cc_proto
)
add_library(cyber::transport::common::endpoint  ALIAS   cyber_transport_common_endpoint)

add_library(cyber_transport_common_identity  SHARED
  identity.cc
)
set_target_properties(cyber_transport_common_identity  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_common_identity
  cyber::common::util
  -luuid
)
add_library(cyber::transport::common::identity  ALIAS   cyber_transport_common_identity)

