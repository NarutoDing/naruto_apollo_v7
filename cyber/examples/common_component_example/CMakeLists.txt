cmake_minimum_required(VERSION 3.16)

project(cyber_examples_common_component_example)
message("${Green} [info] cyber_examples_common_component_example cmakelist ${ColourReset}")

add_library(cyber_examples_common_component_example_common_component_example_lib  SHARED
  common_component_example.cc
)
set_target_properties(cyber_examples_common_component_example_common_component_example_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_examples_common_component_example_common_component_example_lib
  cyber::cyber
  cyber::examples::proto::examples_cc_proto
)
add_library(cyber::examples::common_component_example::common_component_example_lib  ALIAS   cyber_examples_common_component_example_common_component_example_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libcommon_component_example  SHARED
  ${virtual_cc}
)
set_target_properties(libcommon_component_example  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libcommon_component_example
  cyber::examples::common_component_example::common_component_example_lib
)
add_executable(channel_test_writer
  channel_test_writer.cc
)
target_link_libraries(channel_test_writer
  cyber::cyber
  cyber::examples::proto::examples_cc_proto
)
add_executable(channel_prediction_writer
  channel_prediction_writer.cc
)
target_link_libraries(channel_prediction_writer
  cyber::cyber
  cyber::examples::proto::examples_cc_proto
)
