cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_app)
message("${Green} [info] modules_perception_camera_app cmakelist ${ColourReset}")

add_library(modules_perception_camera_app_debug_info  SHARED
  debug_info.cc
)
set_target_properties(modules_perception_camera_app_debug_info  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_app_debug_info
  cyber::cyber
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
)
add_library(modules::perception::camera::app::debug_info  ALIAS   modules_perception_camera_app_debug_info)

add_library(modules_perception_camera_app_obstacle_camera_perception  SHARED
  obstacle_camera_perception.cc
)
set_target_properties(modules_perception_camera_app_obstacle_camera_perception  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_app_obstacle_camera_perception
  modules::perception::camera::app::debug_info
  cyber::cyber
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::camera::app::proto::perception_cc_proto
  modules::perception::camera::common::common
  modules::perception::camera::lib::calibration_service::online_calibration_service::online_calibration_service
  modules::perception::camera::lib::calibrator::laneline::laneline_calibrator
  modules::perception::camera::lib::feature_extractor::tfe::external_feature_extractor
  modules::perception::camera::lib::feature_extractor::tfe::project_feature
  modules::perception::camera::lib::feature_extractor::tfe::tracking_feat_extractor
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::lane::detector::denseline::denseline_lane_detector
  modules::perception::camera::lib::lane::postprocessor::denseline::denseline_lane_postprocessor
  modules::perception::camera::lib::obstacle::detector::smoke::smoke_obstacle_detector
  modules::perception::camera::lib::obstacle::detector::yolo::yolo_obstacle_detector
  modules::perception::camera::lib::obstacle::postprocessor::location_refiner::location_refiner_obstacle_postprocessor
  modules::perception::camera::lib::obstacle::tracker::omt::omt_obstacle_tracker
  modules::perception::camera::lib::obstacle::transformer::multicue::multicue_obstacle_transformer
  modules::perception::camera::lib::obstacle::transformer::singlestage::singlestage_obstacle_transformer
  modules::perception::inference::utils::inference_cuda_util_lib
  modules::perception::inference::utils::inference_util_lib
  ${gflags_LIBRARIES}
)
add_library(modules::perception::camera::app::obstacle_camera_perception  ALIAS   modules_perception_camera_app_obstacle_camera_perception)

add_library(modules_perception_camera_app_obstacle_detection_camera  SHARED
  obstacle_detection_camera.cc
)
set_target_properties(modules_perception_camera_app_obstacle_detection_camera  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_app_obstacle_detection_camera
  modules::perception::camera::app::debug_info
  cyber::cyber
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::camera::app::proto::perception_cc_proto
  modules::perception::camera::common::common
  modules::perception::camera::lib::calibration_service::online_calibration_service::online_calibration_service
  modules::perception::camera::lib::calibrator::laneline::laneline_calibrator
  modules::perception::camera::lib::feature_extractor::tfe::external_feature_extractor
  modules::perception::camera::lib::feature_extractor::tfe::project_feature
  modules::perception::camera::lib::feature_extractor::tfe::tracking_feat_extractor
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::lane::detector::denseline::denseline_lane_detector
  modules::perception::camera::lib::lane::postprocessor::denseline::denseline_lane_postprocessor
  modules::perception::camera::lib::obstacle::detector::smoke::smoke_obstacle_detector
  modules::perception::camera::lib::obstacle::detector::yolo::yolo_obstacle_detector
  modules::perception::camera::lib::obstacle::postprocessor::location_refiner::location_refiner_obstacle_postprocessor
  modules::perception::camera::lib::obstacle::tracker::omt::omt_obstacle_tracker
  modules::perception::camera::lib::obstacle::transformer::multicue::multicue_obstacle_transformer
  modules::perception::camera::lib::obstacle::transformer::singlestage::singlestage_obstacle_transformer
  modules::perception::inference::utils::inference_cuda_util_lib
  modules::perception::inference::utils::inference_util_lib
  ${gflags_LIBRARIES}
)
add_library(modules::perception::camera::app::obstacle_detection_camera  ALIAS   modules_perception_camera_app_obstacle_detection_camera)

add_library(modules_perception_camera_app_traffic_light_camera_perception  SHARED
  traffic_light_camera_perception.cc
)
set_target_properties(modules_perception_camera_app_traffic_light_camera_perception  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_app_traffic_light_camera_perception
  cyber::cyber
  modules::common::util::perf_util
  modules::perception::camera::app::proto::perception_cc_proto
  modules::perception::camera::common::common
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::traffic_light::detector::detection::detection
  modules::perception::camera::lib::traffic_light::detector::recognition::recognition
  modules::perception::camera::lib::traffic_light::proto::detection_cc_proto
  modules::perception::camera::lib::traffic_light::tracker::semantic_decision
  modules::perception::camera::lib::traffic_light::tracker::proto::semantic_cc_proto
  
)
add_library(modules::perception::camera::app::traffic_light_camera_perception  ALIAS   modules_perception_camera_app_traffic_light_camera_perception)

add_library(modules_perception_camera_app_lane_camera_perception  SHARED
  lane_camera_perception.cc
)
set_target_properties(modules_perception_camera_app_lane_camera_perception  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_app_lane_camera_perception
  modules::perception::camera::app::debug_info
  cyber::cyber
  modules::common::util::perf_util
  modules::perception::base::base
  modules::perception::camera::app::proto::perception_cc_proto
  modules::perception::camera::common::common
  modules::perception::camera::lib::calibration_service::online_calibration_service::online_calibration_service
  modules::perception::camera::lib::calibrator::laneline::laneline_calibrator
  modules::perception::camera::lib::interface::interface
  modules::perception::camera::lib::lane::detector::darkSCNN::darkSCNN_lane_detector
  modules::perception::camera::lib::lane::detector::denseline::denseline_lane_detector
  modules::perception::camera::lib::lane::postprocessor::darkSCNN::darkSCNN_lane_postprocessor
  modules::perception::camera::lib::lane::postprocessor::denseline::denseline_lane_postprocessor
  modules::perception::inference::utils::inference_cuda_util_lib
  modules::perception::inference::utils::inference_util_lib
  ${gflags_LIBRARIES}
)
add_library(modules::perception::camera::app::lane_camera_perception  ALIAS   modules_perception_camera_app_lane_camera_perception)

add_library(modules_perception_camera_app_cipv_camera  SHARED
  cipv_camera.cc
)
set_target_properties(modules_perception_camera_app_cipv_camera  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_app_cipv_camera
  cyber::cyber
  modules::common::configs::vehicle_config_helper
  modules::common::math::geometry
  modules::perception::base::base
  modules::perception::camera::common::lane_object
  modules::perception::camera::lib::interface::interface
  
)
add_library(modules::perception::camera::app::cipv_camera  ALIAS   modules_perception_camera_app_cipv_camera)

