cmake_minimum_required(VERSION 3.16)

project(modules_perception_radar_lib_detector_conti_ars_detector)
message("${Green} [info] modules_perception_radar_lib_detector_conti_ars_detector cmakelist ${ColourReset}")

add_library(modules_perception_radar_lib_detector_conti_ars_detector_conti_ars_detector  SHARED
  conti_ars_detector.cc
)
set_target_properties(modules_perception_radar_lib_detector_conti_ars_detector_conti_ars_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_radar_lib_detector_conti_ars_detector_conti_ars_detector
  modules::perception::base::base
  modules::perception::common::geometry::roi_filter
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::registerer::registerer
  modules::perception::radar::common::radar_util
  modules::perception::radar::common::types
  modules::perception::radar::lib::interface::base_detector
  ${eigen}
  
)
add_library(modules::perception::radar::lib::detector::conti_ars_detector::conti_ars_detector  ALIAS   modules_perception_radar_lib_detector_conti_ars_detector_conti_ars_detector)

