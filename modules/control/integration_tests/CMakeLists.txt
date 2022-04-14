cmake_minimum_required(VERSION 3.16)

project(modules_control_integration_tests)
message("${Green} [info] modules_control_integration_tests cmakelist ${ColourReset}")

add_library(modules_control_integration_tests_control_test_base  SHARED
  control_test_base.cc
)
set_target_properties(modules_control_integration_tests_control_test_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_control_integration_tests_control_test_base
  cyber::cyber
  cyber::time::clock
  modules::common::proto::geometry_cc_proto
  modules::control::control_component_lib
  modules::control::common::control_gflags
  
)
add_library(modules::control::integration_tests::control_test_base  ALIAS   modules_control_integration_tests_control_test_base)

