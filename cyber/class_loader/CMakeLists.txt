cmake_minimum_required(VERSION 3.16)

project(cyber_class_loader)
message("${Green} [info] cyber_class_loader cmakelist ${ColourReset}")

add_library(cyber_class_loader_class_loader  SHARED
  class_loader.cc
)
set_target_properties(cyber_class_loader_class_loader  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_class_loader_class_loader
  cyber::class_loader::class_loader_register_macro
  cyber::init
  cyber::class_loader::shared_library::shared_library
  cyber::class_loader::utility::class_factory
  cyber::class_loader::utility::class_loader_utility
  cyber::common::log
)
add_library(cyber::class_loader::class_loader  ALIAS   cyber_class_loader_class_loader)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_class_loader_class_loader_register_macro  SHARED
  ${virtual_cc}
  class_loader_register_macro.h
)
set_target_properties(cyber_class_loader_class_loader_register_macro  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_class_loader_class_loader_register_macro
  cyber::class_loader::utility::class_loader_utility
)
add_library(cyber::class_loader::class_loader_register_macro  ALIAS   cyber_class_loader_class_loader_register_macro)

add_library(cyber_class_loader_class_loader_manager  SHARED
  class_loader_manager.cc
)
set_target_properties(cyber_class_loader_class_loader_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_class_loader_class_loader_manager
  cyber::class_loader::class_loader
)
add_library(cyber::class_loader::class_loader_manager  ALIAS   cyber_class_loader_class_loader_manager)

