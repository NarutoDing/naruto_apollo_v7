cmake_minimum_required(VERSION 3.16)

project(modules_prediction_scenario_right_of_way)
message("${Green} [info] modules_prediction_scenario_right_of_way cmakelist ${ColourReset}")

add_library(modules_prediction_scenario_right_of_way_right_of_way  SHARED
  right_of_way.cc
)
set_target_properties(modules_prediction_scenario_right_of_way_right_of_way  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_scenario_right_of_way_right_of_way
  modules::prediction::container::container_manager
  modules::prediction::container::obstacles::obstacles_container
  modules::prediction::container::pose::pose_container
)
add_library(modules::prediction::scenario::right_of_way::right_of_way  ALIAS   modules_prediction_scenario_right_of_way_right_of_way)

