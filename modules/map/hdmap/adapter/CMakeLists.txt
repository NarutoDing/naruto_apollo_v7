cmake_minimum_required(VERSION 3.16)

project(modules_map_hdmap_adapter)
message("${Green} [info] modules_map_hdmap_adapter cmakelist ${ColourReset}")

add_library(modules_map_hdmap_adapter_opendrive_adapter  SHARED
  opendrive_adapter.cc
)
set_target_properties(modules_map_hdmap_adapter_opendrive_adapter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_opendrive_adapter
  modules::map::hdmap::adapter::coordinate_convert_tool
  modules::map::hdmap::adapter::proto_organizer
  cyber::common::log
  modules::map::hdmap::adapter::xml_parser::xml_parser
)
add_library(modules::map::hdmap::adapter::opendrive_adapter  ALIAS   modules_map_hdmap_adapter_opendrive_adapter)

add_library(modules_map_hdmap_adapter_coordinate_convert_tool  SHARED
  coordinate_convert_tool.cc
)
set_target_properties(modules_map_hdmap_adapter_coordinate_convert_tool  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_coordinate_convert_tool
  modules::map::hdmap::adapter::xml_parser::status
  ${glog_LIBRARIES}
  ${proj}
)
add_library(modules::map::hdmap::adapter::coordinate_convert_tool  ALIAS   modules_map_hdmap_adapter_coordinate_convert_tool)

add_library(modules_map_hdmap_adapter_proto_organizer  SHARED
  proto_organizer.cc
)
set_target_properties(modules_map_hdmap_adapter_proto_organizer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_proto_organizer
  cyber::common::log
  modules::common::math::math
  modules::common::util::util
  modules::map::hdmap::adapter::xml_parser::common_define
  modules::map::proto::map_cc_proto
  ${absl}
)
add_library(modules::map::hdmap::adapter::proto_organizer  ALIAS   modules_map_hdmap_adapter_proto_organizer)

