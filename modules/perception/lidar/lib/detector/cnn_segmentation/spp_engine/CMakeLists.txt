cmake_minimum_required(VERSION 3.16)

project(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine)
message("${Green} [info] modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine cmakelist ${ColourReset}")

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_engine  SHARED
  spp_engine.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_engine  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_engine
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_cluster
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_cluster_list
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_label_image
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_seg_cc_2d
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_struct
  cyber::cyber
  
  ${eigen}
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_engine  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_engine)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_cluster  SHARED
  ${virtual_cc}
  spp_cluster.h
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_cluster  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_cluster
  modules::perception::base::base
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_cluster  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_cluster)

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_cluster_list  SHARED
  spp_cluster_list.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_cluster_list  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_cluster_list
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_cluster
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_label_image
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_pool_types
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_cluster_list  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_cluster_list)

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_label_image  SHARED
  spp_label_image.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_label_image  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_label_image
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_cluster
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_pool_types
  modules::perception::base::base
  modules::perception::common::i_lib::i_lib
  modules::perception::lidar::common::common
  
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_label_image  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_label_image)

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_pool_types  SHARED
  spp_pool_types.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_pool_types  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_pool_types
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_cluster
  modules::perception::base::base
  modules::perception::lidar::common::common
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_pool_types  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_pool_types)

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_seg_cc_2d  SHARED
  spp_seg_cc_2d.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_seg_cc_2d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_seg_cc_2d
  modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_label_image
  cyber::cyber
  modules::perception::base::base
  modules::perception::common::i_lib::i_lib
  modules::perception::lib::thread::thread
  modules::perception::lidar::common::common
  
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_seg_cc_2d  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_seg_cc_2d)

add_library(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_struct  SHARED
  spp_struct.cc
)
set_target_properties(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_struct  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_struct
  modules::perception::base::base
)
add_library(modules::perception::lidar::lib::detector::cnn_segmentation::spp_engine::spp_struct  ALIAS   modules_perception_lidar_lib_detector_cnn_segmentation_spp_engine_spp_struct)

