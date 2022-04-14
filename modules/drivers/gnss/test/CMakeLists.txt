cmake_minimum_required(VERSION 3.16)

project(modules_drivers_gnss_test)
message("${Green} [info] modules_drivers_gnss_test cmakelist ${ColourReset}")

add_executable(parser_cli
  parser_cli.cc
)
target_link_libraries(parser_cli
  cyber::cyber
  modules::drivers::gnss::proto::gnss_status_cc_proto
  modules::drivers::gnss::stream::gnss_stream
  ${gflags_LIBRARIES}
)
