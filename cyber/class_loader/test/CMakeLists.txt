cmake_minimum_required(VERSION 3.16)

project(cyber_class_loader_test)
message("${Green} [info] cyber_class_loader_test cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_class_loader_test_base  SHARED
  ${virtual_cc}
  base.h
)
set_target_properties(cyber_class_loader_test_base  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::class_loader::test::base  ALIAS   cyber_class_loader_test_base)

add_library(cyber_class_loader_test_plugin1  SHARED
  plugin1.cc
)
set_target_properties(cyber_class_loader_test_plugin1  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_class_loader_test_plugin1
  cyber::class_loader::test::base
  cyber::class_loader::class_loader_manager
)
add_library(cyber::class_loader::test::plugin1  ALIAS   cyber_class_loader_test_plugin1)

add_library(cyber_class_loader_test_plugin2  SHARED
  plugin2.cc
)
set_target_properties(cyber_class_loader_test_plugin2  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_class_loader_test_plugin2
  cyber::class_loader::test::base
  cyber::class_loader::class_loader_manager
)
add_library(cyber::class_loader::test::plugin2  ALIAS   cyber_class_loader_test_plugin2)

