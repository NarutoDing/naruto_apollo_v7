cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_app)
message("${Green} [info] modules_perception_fusion_app cmakelist ${ColourReset}")

add_library(modules_perception_fusion_app_obstacle_multi_sensor_fusion  SHARED
  obstacle_multi_sensor_fusion.cc
)
set_target_properties(modules_perception_fusion_app_obstacle_multi_sensor_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_app_obstacle_multi_sensor_fusion
  cyber::cyber
  modules::perception::base::base
  modules::perception::fusion::base::base
  modules::perception::fusion::lib::interface::base_multisensor_fusion
  modules::perception::fusion::lib::interface::base_fusion_system
  modules::perception::fusion::lib::fusion_system::probabilistic_fusion::probabilistic_fusion
  modules::perception::lib::registerer::registerer
  ${eigen}
  
)
add_library(modules::perception::fusion::app::obstacle_multi_sensor_fusion  ALIAS   modules_perception_fusion_app_obstacle_multi_sensor_fusion)

