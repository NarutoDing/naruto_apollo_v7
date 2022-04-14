cmake_minimum_required(VERSION 3.16)

project(cyber_class_loader_shared_library)
message("${Green} [info] cyber_class_loader_shared_library cmakelist ${ColourReset}")

add_library(cyber_class_loader_shared_library_shared_library  SHARED
  shared_library.cc
)
set_target_properties(cyber_class_loader_shared_library_shared_library  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_class_loader_shared_library_shared_library
  -ldl
  cyber::class_loader::shared_library::exceptions
)
add_library(cyber::class_loader::shared_library::shared_library  ALIAS   cyber_class_loader_shared_library_shared_library)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_class_loader_shared_library_exceptions  SHARED
  ${virtual_cc}
  exceptions.h
)
set_target_properties(cyber_class_loader_shared_library_exceptions  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::class_loader::shared_library::exceptions  ALIAS   cyber_class_loader_shared_library_exceptions)

add_library(cyber_class_loader_shared_library_sample_lib  SHARED
  sample.cc
)
set_target_properties(cyber_class_loader_shared_library_sample_lib  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::class_loader::shared_library::sample_lib  ALIAS   cyber_class_loader_shared_library_sample_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libsample  SHARED
  ${virtual_cc}
)
set_target_properties(libsample  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libsample
  cyber::class_loader::shared_library::sample_lib
)
