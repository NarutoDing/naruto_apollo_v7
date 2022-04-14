cmake_minimum_required(VERSION 3.16)

project(cyber_examples)
message("${Green} [info] cyber_examples cmakelist ${ColourReset}")

add_executable(talker
  talker.cc
)
target_link_libraries(talker
  cyber::cyber
  cyber::examples::proto::examples_cc_proto
)
add_executable(listener
  listener.cc
)
target_link_libraries(listener
  cyber::cyber
  cyber::examples::proto::examples_cc_proto
)
add_executable(paramserver
  paramserver.cc
)
target_link_libraries(paramserver
  cyber::cyber
  cyber::parameter::parameter
)
add_executable(service
  service.cc
)
target_link_libraries(service
  cyber::cyber
  cyber::examples::proto::examples_cc_proto
)
add_executable(record
  record.cc
)
target_link_libraries(record
  cyber::cyber
  cyber::proto::record_cc_proto
)
