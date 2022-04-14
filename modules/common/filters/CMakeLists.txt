cmake_minimum_required(VERSION 3.16)

project(modules_common_filters)
message("${Green} [info] modules_common_filters cmakelist ${ColourReset}")

add_library(modules_common_filters_digital_filter  SHARED
  digital_filter.cc
)
set_target_properties(modules_common_filters_digital_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_filters_digital_filter
  modules::common::filters::digital_filter_coefficients
  cyber::common::log
)
add_library(modules::common::filters::digital_filter  ALIAS   modules_common_filters_digital_filter)

add_library(modules_common_filters_mean_filter  SHARED
  mean_filter.cc
)
set_target_properties(modules_common_filters_mean_filter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_filters_mean_filter
  cyber::common::log
)
add_library(modules::common::filters::mean_filter  ALIAS   modules_common_filters_mean_filter)

add_library(modules_common_filters_digital_filter_coefficients  SHARED
  digital_filter_coefficients.cc
)
set_target_properties(modules_common_filters_digital_filter_coefficients  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_filters_digital_filter_coefficients
  cyber::cyber
)
add_library(modules::common::filters::digital_filter_coefficients  ALIAS   modules_common_filters_digital_filter_coefficients)

