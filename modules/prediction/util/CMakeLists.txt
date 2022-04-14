cmake_minimum_required(VERSION 3.16)

project(modules_prediction_util)
message("${Green} [info] modules_prediction_util cmakelist ${ColourReset}")

add_library(modules_prediction_util_data_extraction  SHARED
  data_extraction.cc
)
set_target_properties(modules_prediction_util_data_extraction  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_util_data_extraction
  cyber::cyber
  ${boost}
)
add_library(modules::prediction::util::data_extraction  ALIAS   modules_prediction_util_data_extraction)

