cmake_minimum_required(VERSION 3.16)

project(modules_perception_common_sensor_manager)
message("${Green} [info] modules_perception_common_sensor_manager cmakelist ${ColourReset}")

add_library(modules_perception_common_sensor_manager_sensor_manager  SHARED
  sensor_manager.cc
)
set_target_properties(modules_perception_common_sensor_manager_sensor_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_common_sensor_manager_sensor_manager
  cyber::cyber
  modules::perception::base::base_type
  modules::perception::base::camera
  modules::perception::base::omnidirectional_model
  modules::perception::base::polynomial
  modules::perception::common::io::io_util
  modules::perception::lib::config_manager::config_manager
  modules::perception::lib::thread::thread
  modules::perception::proto::perception_config_schema_cc_proto
  modules::perception::proto::sensor_meta_schema_cc_proto
  ${yaml}
)
add_library(modules::perception::common::sensor_manager::sensor_manager  ALIAS   modules_perception_common_sensor_manager_sensor_manager)

