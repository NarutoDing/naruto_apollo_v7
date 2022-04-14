cmake_minimum_required(VERSION 3.16)

project(modules_perception_base_test)
message("${Green} [info] modules_perception_base_test cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_base_test_test_helper  SHARED
  ${virtual_cc}
  test_helper.h
)
set_target_properties(modules_perception_base_test_test_helper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_base_test_test_helper
  
)
add_library(modules::perception::base::test::test_helper  ALIAS   modules_perception_base_test_test_helper)

