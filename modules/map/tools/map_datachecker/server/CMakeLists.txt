cmake_minimum_required(VERSION 3.16)

project(modules_map_tools_map_datachecker_server)
message("${Green} [info] modules_map_tools_map_datachecker_server cmakelist ${ColourReset}")

add_library(modules_map_tools_map_datachecker_server_channel_verify  SHARED
  channel_verify.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_channel_verify  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_channel_verify
  modules::map::tools::map_datachecker::server::common
  cyber::cyber
  modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto
  ${boost}
)
add_library(modules::map::tools::map_datachecker::server::channel_verify  ALIAS   modules_map_tools_map_datachecker_server_channel_verify)

add_library(modules_map_tools_map_datachecker_server_channel_verify_agent  SHARED
  channel_verify_agent.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_channel_verify_agent  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_channel_verify_agent
  modules::map::tools::map_datachecker::server::channel_verify
  modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto
  modules::map::tools::map_datachecker::proto::collection_service_cc_grpc
  ${grpc}
)
add_library(modules::map::tools::map_datachecker::server::channel_verify_agent  ALIAS   modules_map_tools_map_datachecker_server_channel_verify_agent)

add_library(modules_map_tools_map_datachecker_server_common  SHARED
  common.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_common  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_common
  cyber::cyber
  ${boost}
)
add_library(modules::map::tools::map_datachecker::server::common  ALIAS   modules_map_tools_map_datachecker_server_common)

add_library(modules_map_tools_map_datachecker_server_eight_route  SHARED
  eight_route.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_eight_route  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_eight_route
  modules::map::tools::map_datachecker::server::common
  modules::map::tools::map_datachecker::server::worker_gflags
  cyber::cyber
  modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto
  ${grpc}
)
add_library(modules::map::tools::map_datachecker::server::eight_route  ALIAS   modules_map_tools_map_datachecker_server_eight_route)

add_library(modules_map_tools_map_datachecker_server_laps_checker  SHARED
  laps_checker.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_laps_checker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_laps_checker
  modules::map::tools::map_datachecker::server::common
  modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto
  ${boost}
)
add_library(modules::map::tools::map_datachecker::server::laps_checker  ALIAS   modules_map_tools_map_datachecker_server_laps_checker)

add_library(modules_map_tools_map_datachecker_server_loops_verify_agent  SHARED
  loops_verify_agent.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_loops_verify_agent  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_loops_verify_agent
  modules::map::tools::map_datachecker::server::laps_checker
  modules::map::tools::map_datachecker::server::pose_collection_agent
  modules::map::tools::map_datachecker::proto::collection_service_cc_grpc
  ${grpc}
)
add_library(modules::map::tools::map_datachecker::server::loops_verify_agent  ALIAS   modules_map_tools_map_datachecker_server_loops_verify_agent)

add_library(modules_map_tools_map_datachecker_server_pj_transformer  SHARED
  pj_transformer.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_pj_transformer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_pj_transformer
  cyber::cyber
  ${proj}
)
add_library(modules::map::tools::map_datachecker::server::pj_transformer  ALIAS   modules_map_tools_map_datachecker_server_pj_transformer)

add_library(modules_map_tools_map_datachecker_server_pose_collection  SHARED
  pose_collection.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_pose_collection  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_pose_collection
  modules::map::tools::map_datachecker::server::common
)
add_library(modules::map::tools::map_datachecker::server::pose_collection  ALIAS   modules_map_tools_map_datachecker_server_pose_collection)

add_library(modules_map_tools_map_datachecker_server_pose_collection_agent  SHARED
  pose_collection_agent.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_pose_collection_agent  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_pose_collection_agent
  modules::map::tools::map_datachecker::server::common
  modules::map::tools::map_datachecker::server::pj_transformer
  modules::map::tools::map_datachecker::server::pose_collection
  cyber::cyber
  modules::drivers::gnss::proto::gnss_best_pose_cc_proto
)
add_library(modules::map::tools::map_datachecker::server::pose_collection_agent  ALIAS   modules_map_tools_map_datachecker_server_pose_collection_agent)

add_library(modules_map_tools_map_datachecker_server_static_align  SHARED
  static_align.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_static_align  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_static_align
  modules::map::tools::map_datachecker::server::common
  modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto
)
add_library(modules::map::tools::map_datachecker::server::static_align  ALIAS   modules_map_tools_map_datachecker_server_static_align)

add_library(modules_map_tools_map_datachecker_server_worker  SHARED
  worker.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_worker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_worker
  modules::map::tools::map_datachecker::server::eight_route
  modules::map::tools::map_datachecker::server::static_align
  modules::map::tools::map_datachecker::server::worker_agent
  modules::map::tools::map_datachecker::server::worker_cyber_node
  modules::map::tools::map_datachecker::server::worker_gflags
  cyber::cyber
  ${grpc}
)
add_library(modules::map::tools::map_datachecker::server::worker  ALIAS   modules_map_tools_map_datachecker_server_worker)

add_library(modules_map_tools_map_datachecker_server_worker_agent  SHARED
  worker_agent.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_worker_agent  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_worker_agent
  modules::map::tools::map_datachecker::server::channel_verify_agent
  modules::map::tools::map_datachecker::server::common
  modules::map::tools::map_datachecker::server::eight_route
  modules::map::tools::map_datachecker::server::loops_verify_agent
  modules::map::tools::map_datachecker::server::pose_collection
  modules::map::tools::map_datachecker::server::static_align
  modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto
  modules::map::tools::map_datachecker::proto::collection_service_cc_grpc
  ${grpc}
)
add_library(modules::map::tools::map_datachecker::server::worker_agent  ALIAS   modules_map_tools_map_datachecker_server_worker_agent)

add_library(modules_map_tools_map_datachecker_server_worker_cyber_node  SHARED
  worker_cyber_node.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_worker_cyber_node  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_worker_cyber_node
  modules::map::tools::map_datachecker::server::worker_agent
  modules::map::tools::map_datachecker::server::worker_gflags
  cyber::cyber
  modules::drivers::gnss::proto::gnss_best_pose_cc_proto
  modules::map::tools::map_datachecker::proto::collection_error_code_cc_proto
  modules::map::tools::map_datachecker::proto::collection_service_cc_grpc
)
add_library(modules::map::tools::map_datachecker::server::worker_cyber_node  ALIAS   modules_map_tools_map_datachecker_server_worker_cyber_node)

add_library(modules_map_tools_map_datachecker_server_worker_gflags  SHARED
  worker_gflags.cc
)
set_target_properties(modules_map_tools_map_datachecker_server_worker_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_map_tools_map_datachecker_server_worker_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::map::tools::map_datachecker::server::worker_gflags  ALIAS   modules_map_tools_map_datachecker_server_worker_gflags)

add_executable(map_datachecker_server
  main.cc
)
target_link_libraries(map_datachecker_server
  modules::map::tools::map_datachecker::server::worker
  cyber::cyber
)
