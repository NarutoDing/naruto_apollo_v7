cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_image_processing)
message("${Green} [info] modules_perception_common_image_processing cmakelist ${ColourReset}")

add_library(modules_perception_common_image_processing_hough_transfer  SHARED
  hough_transfer.cc
)
set_target_properties(modules_perception_common_image_processing_hough_transfer  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::common::image_processing::hough_transfer  ALIAS   modules_perception_common_image_processing_hough_transfer)

