cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_gatekeeper_pbf_gatekeeper)
message("${Green} [info] modules_perception_fusion_lib_gatekeeper_pbf_gatekeeper cmakelist ${ColourReset}")

add_library(modules_perception_fusion_lib_gatekeeper_pbf_gatekeeper_pbf_gatekeeper  SHARED
  pbf_gatekeeper.cc
)
set_target_properties(modules_perception_fusion_lib_gatekeeper_pbf_gatekeeper_pbf_gatekeeper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_gatekeeper_pbf_gatekeeper_pbf_gatekeeper
  modules::common::util::util
  modules::perception::fusion::base::base_init_options
  modules::perception::fusion::base::scene
  modules::perception::fusion::base::track
  modules::perception::fusion::lib::gatekeeper::pbf_gatekeeper::proto::pbf_gatekeeper_config_cc_proto
  modules::perception::fusion::lib::interface::interface
  modules::perception::lib::config_manager::config_manager
)
add_library(modules::perception::fusion::lib::gatekeeper::pbf_gatekeeper::pbf_gatekeeper  ALIAS   modules_perception_fusion_lib_gatekeeper_pbf_gatekeeper_pbf_gatekeeper)

