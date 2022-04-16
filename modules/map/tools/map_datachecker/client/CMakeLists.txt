cmake_minimum_required(VERSION 3.16)

project(modules_map_tools_map_datachecker_client)
message("${Green} [info] modules_map_tools_map_datachecker_client cmakelist ${ColourReset}")

add_library(modules_map_tools_map_datachecker_client_client  SHARED
  client.cc
)
set_target_properties(modules_map_tools_map_datachecker_client_client  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_client_client
  modules::map::tools::map_datachecker::client::client_channel_checker
  modules::map::tools::map_datachecker::client::client_common
  modules::map::tools::map_datachecker::client::client_gflags
  modules::map::tools::map_datachecker::client::client_loops_check
  cyber::cyber
  ${boost}
  ${grpc}
  ${yaml}
)
add_library(modules::map::tools::map_datachecker::client::client  ALIAS   modules_map_tools_map_datachecker_client_client)

add_library(modules_map_tools_map_datachecker_client_client_channel_checker  SHARED
  client_channel_checker.cc
)
set_target_properties(modules_map_tools_map_datachecker_client_client_channel_checker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_client_client_channel_checker
  modules::map::tools::map_datachecker::client::client_common
  modules::map::tools::map_datachecker::client::client_gflags
  modules::map::tools::map_datachecker::client::exception_handler
  cyber::cyber
  modules::map::tools::map_datachecker::proto::collection_service_cc_proto
  ${boost}
  ${grpc}
  ${yaml}
)
add_library(modules::map::tools::map_datachecker::client::client_channel_checker  ALIAS   modules_map_tools_map_datachecker_client_client_channel_checker)

add_library(modules_map_tools_map_datachecker_client_client_common  SHARED
  client_common.cc
)
set_target_properties(modules_map_tools_map_datachecker_client_client_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_client_client_common
  cyber::cyber
  ${boost}
  ${grpc}
)
add_library(modules::map::tools::map_datachecker::client::client_common  ALIAS   modules_map_tools_map_datachecker_client_client_common)

add_library(modules_map_tools_map_datachecker_client_client_gflags  SHARED
  client_gflags.cc
)
set_target_properties(modules_map_tools_map_datachecker_client_client_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_client_client_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::map::tools::map_datachecker::client::client_gflags  ALIAS   modules_map_tools_map_datachecker_client_client_gflags)

add_library(modules_map_tools_map_datachecker_client_client_loops_check  SHARED
  client_loops_check.cc
)
set_target_properties(modules_map_tools_map_datachecker_client_client_loops_check  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_client_client_loops_check
  modules::map::tools::map_datachecker::client::client_common
  modules::map::tools::map_datachecker::client::client_gflags
  modules::map::tools::map_datachecker::client::exception_handler
  cyber::cyber
  modules::map::tools::map_datachecker::proto::collection_service_cc_proto
  ${boost}
  ${grpc}
  ${yaml}
)
add_library(modules::map::tools::map_datachecker::client::client_loops_check  ALIAS   modules_map_tools_map_datachecker_client_client_loops_check)

add_library(modules_map_tools_map_datachecker_client_exception_handler  SHARED
  exception_handler.cc
)
set_target_properties(modules_map_tools_map_datachecker_client_exception_handler  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_client_exception_handler
  modules::map::tools::map_datachecker::client::client_common
  cyber::cyber
  modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto
)
add_library(modules::map::tools::map_datachecker::client::exception_handler  ALIAS   modules_map_tools_map_datachecker_client_exception_handler)

add_executable(map_datachecker_client
  main.cc
)
target_link_libraries(map_datachecker_client
  modules::map::tools::map_datachecker::client::client
  modules::map::tools::map_datachecker::client::client_gflags
  ${boost}
  ${grpc}
)
