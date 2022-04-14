cmake_minimum_required(VERSION 3.16)

project(modules_common_util)
message("${Green} [info] modules_common_util cmakelist ${ColourReset}")

add_library(modules_common_util_util  SHARED
  util.cc
)
set_target_properties(modules_common_util_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_util
  cyber::common::log
  cyber::common::types
  modules::common::configs::config_gflags
  modules::common::math::math
  modules::common::math::geometry
  modules::common::proto::geometry_cc_proto
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::common::util::util  ALIAS   modules_common_util_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_future  SHARED
  ${virtual_cc}
  future.h
)
set_target_properties(modules_common_util_future  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_future
  ${absl}
)
add_library(modules::common::util::future  ALIAS   modules_common_util_future)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_point_factory  SHARED
  ${virtual_cc}
  point_factory.h
)
set_target_properties(modules_common_util_point_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_point_factory
  modules::common::math::geometry
  modules::common::proto::pnc_point_cc_proto
)
add_library(modules::common::util::point_factory  ALIAS   modules_common_util_point_factory)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_lru_cache  SHARED
  ${virtual_cc}
  lru_cache.h
)
set_target_properties(modules_common_util_lru_cache  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::util::lru_cache  ALIAS   modules_common_util_lru_cache)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_color  SHARED
  ${virtual_cc}
  color.h
)
set_target_properties(modules_common_util_color  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::common::util::color  ALIAS   modules_common_util_color)

add_library(modules_common_util_string_util  SHARED
  string_util.cc
)
set_target_properties(modules_common_util_string_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_string_util
  modules::common::util::future
  ${absl}
)
add_library(modules::common::util::string_util  ALIAS   modules_common_util_string_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_message_util  SHARED
  ${virtual_cc}
  message_util.h
)
set_target_properties(modules_common_util_message_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_message_util
  cyber::common::file
  cyber::time::clock
  ${absl}
  ${Protobuf_LIBRARIES}
)
add_library(modules::common::util::message_util  ALIAS   modules_common_util_message_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_time_util  SHARED
  ${virtual_cc}
  time_util.h
)
set_target_properties(modules_common_util_time_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_time_util
  cyber::common::macros
)
add_library(modules::common::util::time_util  ALIAS   modules_common_util_time_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_map_util  SHARED
  ${virtual_cc}
  map_util.h
)
set_target_properties(modules_common_util_map_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_map_util
  ${Protobuf_LIBRARIES}
)
add_library(modules::common::util::map_util  ALIAS   modules_common_util_map_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_factory  SHARED
  ${virtual_cc}
  factory.h
)
set_target_properties(modules_common_util_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_factory
  cyber::common::common
)
add_library(modules::common::util::factory  ALIAS   modules_common_util_factory)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_points_downsampler  SHARED
  ${virtual_cc}
  points_downsampler.h
)
set_target_properties(modules_common_util_points_downsampler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_points_downsampler
  cyber::common::common
  modules::common::math::geometry
)
add_library(modules::common::util::points_downsampler  ALIAS   modules_common_util_points_downsampler)

add_library(modules_common_util_json_util  SHARED
  json_util.cc
)
set_target_properties(modules_common_util_json_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_json_util
  cyber::common::common
  ${json}
  ${Protobuf_LIBRARIES}
)
add_library(modules::common::util::json_util  ALIAS   modules_common_util_json_util)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_common_util_eigen_defs  SHARED
  ${virtual_cc}
  eigen_defs.h
)
set_target_properties(modules_common_util_eigen_defs  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_eigen_defs
  ${eigen}
)
add_library(modules::common::util::eigen_defs  ALIAS   modules_common_util_eigen_defs)

add_library(modules_common_util_perf_util  SHARED
  perf_util.cc
)
set_target_properties(modules_common_util_perf_util  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_util_perf_util
  cyber::common::log
  cyber::common::macros
  cyber::time::time
  ${absl}
)
add_library(modules::common::util::perf_util  ALIAS   modules_common_util_perf_util)

