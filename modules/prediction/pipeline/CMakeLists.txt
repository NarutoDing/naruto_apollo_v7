cmake_minimum_required(VERSION 3.16)

project(modules_prediction_pipeline)
message("${Green} [info] modules_prediction_pipeline cmakelist ${ColourReset}")

add_library(modules_prediction_pipeline_vector_net  SHARED
  vector_net.cc
)
set_target_properties(modules_prediction_pipeline_vector_net  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_prediction_pipeline_vector_net
  cyber::common::file
  modules::common::math::linear_interpolation
  modules::common::util::point_factory
  modules::map::hdmap::hdmap_util
  modules::prediction::common::prediction_system_gflags
  modules::prediction::proto::vector_net_cc_proto
)
add_library(modules::prediction::pipeline::vector_net  ALIAS   modules_prediction_pipeline_vector_net)

add_executable(records_to_offline_data
  records_to_offline_data.cc
)
target_link_libraries(records_to_offline_data
  modules::prediction::common::message_process
  ${boost}
  ${absl}
)
add_executable(vector_net_feature
  vector_net_feature.cc
)
target_link_libraries(vector_net_feature
  modules::prediction::pipeline::vector_net
)
add_executable(vector_net_offline_data
  vector_net_offline_data.cc
)
target_link_libraries(vector_net_offline_data
  modules::prediction::pipeline::vector_net
)
