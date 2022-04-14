cmake_minimum_required(VERSION 3.16)

project(cyber_sysmo)
message("${Green} [info] cyber_sysmo cmakelist ${ColourReset}")

add_library(cyber_sysmo_sysmo  SHARED
  sysmo.cc
)
set_target_properties(cyber_sysmo_sysmo  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_sysmo_sysmo
  cyber::scheduler::scheduler_factory
)
add_library(cyber::sysmo::sysmo  ALIAS   cyber_sysmo_sysmo)

