cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_lib_preprocessor_conti_ars_preprocessor)
message("${Green} [info] modules_perception_radar_lib_preprocessor_conti_ars_preprocessor cmakelist ${ColourReset}")

add_library(modules_perception_radar_lib_preprocessor_conti_ars_preprocessor_conti_ars_preprocessor  SHARED
  conti_ars_preprocessor.cc
)
set_target_properties(modules_perception_radar_lib_preprocessor_conti_ars_preprocessor_conti_ars_preprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_preprocessor_conti_ars_preprocessor_conti_ars_preprocessor
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::registerer::registerer
  modules::perception::radar::common::types
  modules::perception::radar::lib::interface::base_preprocessor
  ${eigen}
  
)
add_library(modules::perception::radar::lib::preprocessor::conti_ars_preprocessor::conti_ars_preprocessor  ALIAS   modules_perception_radar_lib_preprocessor_conti_ars_preprocessor_conti_ars_preprocessor)

