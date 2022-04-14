cmake_minimum_required(VERSION 3.16)

project(modules_map_hdmap_adapter_xml_parser)
message("${Green} [info] modules_map_hdmap_adapter_xml_parser cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_map_hdmap_adapter_xml_parser_xml_parser  SHARED
  ${virtual_cc}
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_xml_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_xml_parser
  modules::map::hdmap::adapter::xml_parser::header_xml_parser
  modules::map::hdmap::adapter::xml_parser::junctions_xml_parser
  modules::map::hdmap::adapter::xml_parser::lanes_xml_parser
  modules::map::hdmap::adapter::xml_parser::objects_xml_parser
  modules::map::hdmap::adapter::xml_parser::roads_xml_parser
  modules::map::hdmap::adapter::xml_parser::signals_xml_parser
  modules::map::hdmap::adapter::xml_parser::status
)
add_library(modules::map::hdmap::adapter::xml_parser::xml_parser  ALIAS   modules_map_hdmap_adapter_xml_parser_xml_parser)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_map_hdmap_adapter_xml_parser_common_define  SHARED
  ${virtual_cc}
  common_define.h
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_common_define  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_common_define
  cyber::common::log
  modules::map::proto::map_cc_proto
)
add_library(modules::map::hdmap::adapter::xml_parser::common_define  ALIAS   modules_map_hdmap_adapter_xml_parser_common_define)

add_library(modules_map_hdmap_adapter_xml_parser_header_xml_parser  SHARED
  header_xml_parser.cc
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_header_xml_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_header_xml_parser
  modules::map::hdmap::adapter::xml_parser::common_define
  modules::map::hdmap::adapter::xml_parser::status
  modules::map::hdmap::adapter::xml_parser::util_xml_parser
  modules::map::hdmap::adapter::coordinate_convert_tool
  ${absl}
  ${tinyxml2}
)
add_library(modules::map::hdmap::adapter::xml_parser::header_xml_parser  ALIAS   modules_map_hdmap_adapter_xml_parser_header_xml_parser)

add_library(modules_map_hdmap_adapter_xml_parser_junctions_xml_parser  SHARED
  junctions_xml_parser.cc
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_junctions_xml_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_junctions_xml_parser
  modules::map::hdmap::adapter::xml_parser::common_define
  modules::map::hdmap::adapter::xml_parser::status
  modules::map::hdmap::adapter::xml_parser::util_xml_parser
  ${tinyxml2}
)
add_library(modules::map::hdmap::adapter::xml_parser::junctions_xml_parser  ALIAS   modules_map_hdmap_adapter_xml_parser_junctions_xml_parser)

add_library(modules_map_hdmap_adapter_xml_parser_lanes_xml_parser  SHARED
  lanes_xml_parser.cc
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_lanes_xml_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_lanes_xml_parser
  modules::map::hdmap::adapter::xml_parser::common_define
  modules::map::hdmap::adapter::xml_parser::status
  modules::map::hdmap::adapter::xml_parser::util_xml_parser
  ${tinyxml2}
)
add_library(modules::map::hdmap::adapter::xml_parser::lanes_xml_parser  ALIAS   modules_map_hdmap_adapter_xml_parser_lanes_xml_parser)

add_library(modules_map_hdmap_adapter_xml_parser_objects_xml_parser  SHARED
  objects_xml_parser.cc
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_objects_xml_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_objects_xml_parser
  modules::map::hdmap::adapter::xml_parser::common_define
  modules::map::hdmap::adapter::xml_parser::status
  modules::map::hdmap::adapter::xml_parser::util_xml_parser
  ${tinyxml2}
)
add_library(modules::map::hdmap::adapter::xml_parser::objects_xml_parser  ALIAS   modules_map_hdmap_adapter_xml_parser_objects_xml_parser)

add_library(modules_map_hdmap_adapter_xml_parser_roads_xml_parser  SHARED
  roads_xml_parser.cc
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_roads_xml_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_roads_xml_parser
  modules::map::hdmap::adapter::xml_parser::common_define
  modules::map::hdmap::adapter::xml_parser::lanes_xml_parser
  modules::map::hdmap::adapter::xml_parser::objects_xml_parser
  modules::map::hdmap::adapter::xml_parser::signals_xml_parser
  modules::map::hdmap::adapter::xml_parser::status
  modules::map::hdmap::adapter::xml_parser::util_xml_parser
  ${tinyxml2}
)
add_library(modules::map::hdmap::adapter::xml_parser::roads_xml_parser  ALIAS   modules_map_hdmap_adapter_xml_parser_roads_xml_parser)

add_library(modules_map_hdmap_adapter_xml_parser_signals_xml_parser  SHARED
  signals_xml_parser.cc
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_signals_xml_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_signals_xml_parser
  modules::map::hdmap::adapter::xml_parser::common_define
  modules::map::hdmap::adapter::xml_parser::status
  modules::map::hdmap::adapter::xml_parser::util_xml_parser
  ${tinyxml2}
)
add_library(modules::map::hdmap::adapter::xml_parser::signals_xml_parser  ALIAS   modules_map_hdmap_adapter_xml_parser_signals_xml_parser)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_map_hdmap_adapter_xml_parser_status  SHARED
  ${virtual_cc}
  status.h
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_status  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_status
  modules::common::status::status
)
add_library(modules::map::hdmap::adapter::xml_parser::status  ALIAS   modules_map_hdmap_adapter_xml_parser_status)

add_library(modules_map_hdmap_adapter_xml_parser_util_xml_parser  SHARED
  util_xml_parser.cc
)
set_target_properties(modules_map_hdmap_adapter_xml_parser_util_xml_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_hdmap_adapter_xml_parser_util_xml_parser
  modules::map::hdmap::adapter::xml_parser::common_define
  modules::map::hdmap::adapter::xml_parser::status
  cyber::common::log
  modules::map::hdmap::adapter::coordinate_convert_tool
  ${tinyxml2}
)
add_library(modules::map::hdmap::adapter::xml_parser::util_xml_parser  ALIAS   modules_map_hdmap_adapter_xml_parser_util_xml_parser)

