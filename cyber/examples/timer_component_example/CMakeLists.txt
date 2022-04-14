cmake_minimum_required(VERSION 3.16)

project(cyber_examples_timer_component_example)
message("${Green} [info] cyber_examples_timer_component_example cmakelist ${ColourReset}")

add_library(cyber_examples_timer_component_example_timer_component_example_lib  SHARED
  timer_component_example.cc
)
set_target_properties(cyber_examples_timer_component_example_timer_component_example_lib  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_examples_timer_component_example_timer_component_example_lib
  cyber::cyber
  cyber::examples::proto::examples_cc_proto
)
add_library(cyber::examples::timer_component_example::timer_component_example_lib  ALIAS   cyber_examples_timer_component_example_timer_component_example_lib)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(libtimer_component_example  SHARED
  ${virtual_cc}
)
set_target_properties(libtimer_component_example  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libtimer_component_example
  cyber::examples::timer_component_example::timer_component_example_lib
)
