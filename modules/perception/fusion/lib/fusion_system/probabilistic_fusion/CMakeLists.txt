cmake_minimum_required(VERSION 3.16)

project(modules_perception_fusion_lib_fusion_system_probabilistic_fusion)
message("${Green} [info] modules_perception_fusion_lib_fusion_system_probabilistic_fusion cmakelist ${ColourReset}")

add_library(modules_perception_fusion_lib_fusion_system_probabilistic_fusion_probabilistic_fusion  SHARED
  probabilistic_fusion.cc
)
set_target_properties(modules_perception_fusion_lib_fusion_system_probabilistic_fusion_probabilistic_fusion  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_fusion_lib_fusion_system_probabilistic_fusion_probabilistic_fusion
  cyber::cyber
  modules::common::util::util
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::common::perception_gflags
  modules::perception::common::graph::graph
  modules::perception::fusion::base::base
  modules::perception::fusion::common::camera_util
  modules::perception::fusion::common::dst_evidence
  modules::perception::fusion::lib::data_association::hm_data_association::chi_squared_cdf
  modules::perception::fusion::lib::data_association::hm_data_association::hm_tracks_objects_match
  modules::perception::fusion::lib::data_association::hm_data_association::track_object_distance
  modules::perception::fusion::lib::data_fusion::existence_fusion::dst_existence_fusion::dst_existence_fusion
  modules::perception::fusion::lib::data_fusion::tracker::pbf_tracker::pbf_tracker
  modules::perception::fusion::lib::data_fusion::type_fusion::dst_type_fusion::dst_type_fusion
  modules::perception::fusion::lib::gatekeeper::pbf_gatekeeper::pbf_gatekeeper
  modules::perception::fusion::lib::interface::interface
  modules::perception::fusion::lib::interface::base_fusion_system
  modules::perception::lib::thread::thread
  modules::perception::proto::probabilistic_fusion_config_cc_proto
  ${eigen}
  
)
add_library(modules::perception::fusion::lib::fusion_system::probabilistic_fusion::probabilistic_fusion  ALIAS   modules_perception_fusion_lib_fusion_system_probabilistic_fusion_probabilistic_fusion)

