cmake_minimum_required(VERSION 3.16)

project(modules_planning_learning_based_img_feature_renderer)
message("${Green} [info] modules_planning_learning_based_img_feature_renderer cmakelist ${ColourReset}")

add_library(modules_planning_learning_based_img_feature_renderer_birdview_img_feature_renderer  SHARED
  birdview_img_feature_renderer.cc
)
set_target_properties(modules_planning_learning_based_img_feature_renderer_birdview_img_feature_renderer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_learning_based_img_feature_renderer_birdview_img_feature_renderer
  cyber::common::common
  modules::common::configs::vehicle_config_helper
  modules::common::util::util
  modules::map::hdmap::hdmap_util
  modules::perception::proto::traffic_light_detection_cc_proto
  modules::planning::proto::learning_data_cc_proto
  modules::planning::proto::planning_semantic_map_config_cc_proto
  ${opencv}
)
add_library(modules::planning::learning_based::img_feature_renderer::birdview_img_feature_renderer  ALIAS   modules_planning_learning_based_img_feature_renderer_birdview_img_feature_renderer)

