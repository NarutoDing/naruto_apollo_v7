cmake_minimum_required(VERSION 3.16)

project(modules_perception_lib_config_manager)
message("${Green} [info] modules_perception_lib_config_manager cmakelist ${ColourReset}")

add_library(modules_perception_lib_config_manager_config_manager  SHARED
  config_manager.cc
)
set_target_properties(modules_perception_lib_config_manager_config_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lib_config_manager_config_manager
  cyber::cyber
  modules::perception::common::perception_gflags
  modules::perception::common::io::io_util
  modules::perception::lib::thread::thread
  modules::perception::proto::perception_config_schema_cc_proto
  ${eigen}
)
add_library(modules::perception::lib::config_manager::config_manager  ALIAS   modules_perception_lib_config_manager_config_manager)

