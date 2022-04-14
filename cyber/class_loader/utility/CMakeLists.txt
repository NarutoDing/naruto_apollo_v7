cmake_minimum_required(VERSION 3.16)

project(cyber_class_loader_utility)
message("${Green} [info] cyber_class_loader_utility cmakelist ${ColourReset}")

add_library(cyber_class_loader_utility_class_factory  SHARED
  class_factory.cc
)
set_target_properties(cyber_class_loader_utility_class_factory  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::class_loader::utility::class_factory  ALIAS   cyber_class_loader_utility_class_factory)

add_library(cyber_class_loader_utility_class_loader_utility  SHARED
  class_loader_utility.cc
)
set_target_properties(cyber_class_loader_utility_class_loader_utility  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_class_loader_utility_class_loader_utility
  cyber::class_loader::utility::class_factory
  cyber::class_loader::shared_library::shared_library
  cyber::common::log
)
add_library(cyber::class_loader::utility::class_loader_utility  ALIAS   cyber_class_loader_utility_class_loader_utility)

