cmake_minimum_required(VERSION 3.16)

project(modules_common_status)
message("${Green} [info] modules_common_status cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_status_status  SHARED
  ${virtual_cc}
  status.h
)
set_target_properties(modules_common_status_status  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_status_status
  modules::common::proto::error_code_cc_proto
  modules::common::util::future
  ${Protobuf_LIBRARIES}
)
add_library(modules::common::status::status  ALIAS   modules_common_status_status)

