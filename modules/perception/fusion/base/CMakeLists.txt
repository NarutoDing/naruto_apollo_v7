cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_base)
message("${Green} [info] modules_perception_fusion_base cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_fusion_base_base  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_fusion_base_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_base_base
  modules::perception::fusion::base::base_forward_declaration
  modules::perception::fusion::base::base_init_options
  modules::perception::fusion::base::fusion_log
  modules::perception::fusion::base::scene
  modules::perception::fusion::base::sensor
  modules::perception::fusion::base::sensor_data_manager
  modules::perception::fusion::base::track
  modules::perception::fusion::base::track_pool_types
)
add_library(modules::perception::fusion::base::base  ALIAS   modules_perception_fusion_base_base)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_fusion_base_base_forward_declaration  SHARED
  ${virtual_cc}
  base_forward_declaration.h
)
set_target_properties(modules_perception_fusion_base_base_forward_declaration  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::fusion::base::base_forward_declaration  ALIAS   modules_perception_fusion_base_base_forward_declaration)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_fusion_base_fusion_log  SHARED
  ${virtual_cc}
  fusion_log.h
)
set_target_properties(modules_perception_fusion_base_fusion_log  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::fusion::base::fusion_log  ALIAS   modules_perception_fusion_base_fusion_log)

add_library(modules_perception_fusion_base_base_init_options  SHARED
  base_init_options.cc
)
set_target_properties(modules_perception_fusion_base_base_init_options  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_base_base_init_options
  modules::perception::lib::config_manager::config_manager
)
add_library(modules::perception::fusion::base::base_init_options  ALIAS   modules_perception_fusion_base_base_init_options)

add_library(modules_perception_fusion_base_scene  SHARED
  scene.cc
)
set_target_properties(modules_perception_fusion_base_scene  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_base_scene
  modules::perception::fusion::base::sensor
  modules::perception::fusion::base::track
)
add_library(modules::perception::fusion::base::scene  ALIAS   modules_perception_fusion_base_scene)

add_library(modules_perception_fusion_base_sensor  SHARED
  sensor.cc
  sensor_frame.cc
  sensor_object.cc
)
set_target_properties(modules_perception_fusion_base_sensor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_base_sensor
  modules::perception::fusion::base::base_forward_declaration
  cyber::cyber
  modules::perception::base::base
  modules::perception::base::base_type
  modules::perception::base::frame
  modules::perception::base::object
  modules::perception::base::object_pool_types
  modules::perception::common::sensor_manager::sensor_manager
  
  ${eigen}
)
add_library(modules::perception::fusion::base::sensor  ALIAS   modules_perception_fusion_base_sensor)

add_library(modules_perception_fusion_base_sensor_data_manager  SHARED
  sensor_data_manager.cc
)
set_target_properties(modules_perception_fusion_base_sensor_data_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_base_sensor_data_manager
  modules::perception::fusion::base::sensor
  modules::perception::base::frame
  modules::perception::common::sensor_manager::sensor_manager
  modules::perception::lib::thread::thread
  
)
add_library(modules::perception::fusion::base::sensor_data_manager  ALIAS   modules_perception_fusion_base_sensor_data_manager)

add_library(modules_perception_fusion_base_track  SHARED
  track.cc
)
set_target_properties(modules_perception_fusion_base_track  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_base_track
  modules::perception::fusion::base::sensor
  
)
add_library(modules::perception::fusion::base::track  ALIAS   modules_perception_fusion_base_track)

add_library(modules_perception_fusion_base_track_pool_types  SHARED
  track_pool_types.cc
)
set_target_properties(modules_perception_fusion_base_track_pool_types  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_base_track_pool_types
  modules::perception::fusion::base::track
  modules::perception::base::object_pool
)
add_library(modules::perception::fusion::base::track_pool_types  ALIAS   modules_perception_fusion_base_track_pool_types)

