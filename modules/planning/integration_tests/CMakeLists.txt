cmake_minimum_required(VERSION 3.16)

project(modules_planning_integration_tests)
message("${Green} [info] modules_planning_integration_tests cmakelist ${ColourReset}")

add_library(modules_planning_integration_tests_planning_test_base  SHARED
  planning_test_base.cc
)
set_target_properties(modules_planning_integration_tests_planning_test_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_integration_tests_planning_test_base
  cyber::common::log
  modules::common::adapters::adapter_gflags
  modules::common::configs::config_gflags
  modules::common::util::util
  modules::common::vehicle_state::vehicle_state_provider
  modules::planning::planning_component_lib
  
)
add_library(modules::planning::integration_tests::planning_test_base  ALIAS   modules_planning_integration_tests_planning_test_base)

