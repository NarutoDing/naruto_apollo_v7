cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_tool_data_extraction)
message("${Green} [info] modules_localization_msf_local_tool_data_extraction cmakelist ${ColourReset}")

add_library(modules_localization_msf_local_tool_data_extraction_data_extraction  SHARED
  cyber_record_reader.cc
  location_exporter.cc
  pcd_exporter.cc
)
set_target_properties(modules_localization_msf_local_tool_data_extraction_data_extraction  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_tool_data_extraction_data_extraction
  cyber::cyber
  modules::common::math::math
  modules::drivers::proto::pointcloud_cc_proto
  modules::localization::msf::common::io::common_io
  modules::localization::proto::gps_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::localization::proto::measure_cc_proto
  ${boost}
  ${eigen}
  ${pcl}
)
add_library(modules::localization::msf::local_tool::data_extraction::data_extraction  ALIAS   modules_localization_msf_local_tool_data_extraction_data_extraction)

add_executable(cyber_record_parser
  cyber_record_parser.cc
)
target_link_libraries(cyber_record_parser
  modules::localization::msf::local_tool::data_extraction::data_extraction
  cyber::cyber
  ${boost}
  ${eigen}
  ${pcl}
)
add_executable(compare_poses
  compare_poses.cc
)
target_link_libraries(compare_poses
  modules::localization::msf::local_tool::data_extraction::data_extraction
  cyber::cyber
  ${boost}
  ${eigen}
)
