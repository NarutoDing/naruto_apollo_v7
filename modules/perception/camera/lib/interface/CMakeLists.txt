cmake_minimum_required(VERSION 3.16)

project(modules_perception_camera_lib_interface)
message("${Green} [info] modules_perception_camera_lib_interface cmakelist ${ColourReset}")

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_lane_postprocessor  SHARED
  ${virtual_cc}
  base_lane_postprocessor.h
)
set_target_properties(modules_perception_camera_lib_interface_base_lane_postprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_lane_postprocessor
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_lane_postprocessor  ALIAS   modules_perception_camera_lib_interface_base_lane_postprocessor)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_calibrator  SHARED
  ${virtual_cc}
  base_calibrator.h
)
set_target_properties(modules_perception_camera_lib_interface_base_calibrator  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_calibrator
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_calibrator  ALIAS   modules_perception_camera_lib_interface_base_calibrator)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_cipv  SHARED
  ${virtual_cc}
  base_cipv.h
)
set_target_properties(modules_perception_camera_lib_interface_base_cipv  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_cipv
  cyber::cyber
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
  ${eigen}
)
add_library(modules::perception::camera::lib::interface::base_cipv  ALIAS   modules_perception_camera_lib_interface_base_cipv)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_tl_preprocessor  SHARED
  ${virtual_cc}
  base_tl_preprocessor.h
)
set_target_properties(modules_perception_camera_lib_interface_base_tl_preprocessor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_tl_preprocessor
  cyber::cyber
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::lib::registerer::registerer
  modules::perception::camera::lib::traffic_light::preprocessor::pose
  modules::perception::base::traffic_light
)
add_library(modules::perception::camera::lib::interface::base_tl_preprocessor  ALIAS   modules_perception_camera_lib_interface_base_tl_preprocessor)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_lane_detector  SHARED
  ${virtual_cc}
  base_lane_detector.h
)
set_target_properties(modules_perception_camera_lib_interface_base_lane_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_lane_detector
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_lane_detector  ALIAS   modules_perception_camera_lib_interface_base_lane_detector)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_landmark_detector  SHARED
  ${virtual_cc}
  base_landmark_detector.h
)
set_target_properties(modules_perception_camera_lib_interface_base_landmark_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_landmark_detector
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_landmark_detector  ALIAS   modules_perception_camera_lib_interface_base_landmark_detector)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_calibration_service  SHARED
  ${virtual_cc}
  base_calibration_service.h
)
set_target_properties(modules_perception_camera_lib_interface_base_calibration_service  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_calibration_service
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_calibration_service  ALIAS   modules_perception_camera_lib_interface_base_calibration_service)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_obstacle_postprocessor  SHARED
  ${virtual_cc}
  base_obstacle_postprocessor.h
)
set_target_properties(modules_perception_camera_lib_interface_base_obstacle_postprocessor  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::camera::lib::interface::base_obstacle_postprocessor  ALIAS   modules_perception_camera_lib_interface_base_obstacle_postprocessor)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_obstacle_tracker  SHARED
  ${virtual_cc}
  base_obstacle_tracker.h
)
set_target_properties(modules_perception_camera_lib_interface_base_obstacle_tracker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_obstacle_tracker
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_obstacle_tracker  ALIAS   modules_perception_camera_lib_interface_base_obstacle_tracker)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_obstacle_transformer  SHARED
  ${virtual_cc}
  base_obstacle_transformer.h
)
set_target_properties(modules_perception_camera_lib_interface_base_obstacle_transformer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_obstacle_transformer
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_obstacle_transformer  ALIAS   modules_perception_camera_lib_interface_base_obstacle_transformer)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_scene_parser  SHARED
  ${virtual_cc}
  base_scene_parser.h
)
set_target_properties(modules_perception_camera_lib_interface_base_scene_parser  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_scene_parser
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_scene_parser  ALIAS   modules_perception_camera_lib_interface_base_scene_parser)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_lane_tracker  SHARED
  ${virtual_cc}
  base_lane_tracker.h
)
set_target_properties(modules_perception_camera_lib_interface_base_lane_tracker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_lane_tracker
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_lane_tracker  ALIAS   modules_perception_camera_lib_interface_base_lane_tracker)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_traffic_light_detector  SHARED
  ${virtual_cc}
  base_traffic_light_detector.h
)
set_target_properties(modules_perception_camera_lib_interface_base_traffic_light_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_traffic_light_detector
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_traffic_light_detector  ALIAS   modules_perception_camera_lib_interface_base_traffic_light_detector)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_init_options  SHARED
  ${virtual_cc}
  base_init_options.h
)
set_target_properties(modules_perception_camera_lib_interface_base_init_options  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::perception::camera::lib::interface::base_init_options  ALIAS   modules_perception_camera_lib_interface_base_init_options)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_obstacle_detector  SHARED
  ${virtual_cc}
  base_obstacle_detector.h
)
set_target_properties(modules_perception_camera_lib_interface_base_obstacle_detector  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_obstacle_detector
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_obstacle_detector  ALIAS   modules_perception_camera_lib_interface_base_obstacle_detector)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_traffic_light_tracker  SHARED
  ${virtual_cc}
  base_traffic_light_tracker.h
)
set_target_properties(modules_perception_camera_lib_interface_base_traffic_light_tracker  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_traffic_light_tracker
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_traffic_light_tracker  ALIAS   modules_perception_camera_lib_interface_base_traffic_light_tracker)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_feature_extractor  SHARED
  ${virtual_cc}
  base_feature_extractor.h
)
set_target_properties(modules_perception_camera_lib_interface_base_feature_extractor  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_feature_extractor
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_feature_extractor  ALIAS   modules_perception_camera_lib_interface_base_feature_extractor)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_inference_engine  SHARED
  ${virtual_cc}
  base_inference_engine.h
)
set_target_properties(modules_perception_camera_lib_interface_base_inference_engine  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_inference_engine
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::base::base
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_inference_engine  ALIAS   modules_perception_camera_lib_interface_base_inference_engine)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_base_camera_perception  SHARED
  ${virtual_cc}
  base_camera_perception.h
)
set_target_properties(modules_perception_camera_lib_interface_base_camera_perception  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_base_camera_perception
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::common::common
  modules::perception::lib::registerer::registerer
)
add_library(modules::perception::camera::lib::interface::base_camera_perception  ALIAS   modules_perception_camera_lib_interface_base_camera_perception)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_perception_camera_lib_interface_interface  SHARED
  ${virtual_cc}
)
set_target_properties(modules_perception_camera_lib_interface_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_perception_camera_lib_interface_interface
  modules::perception::camera::lib::interface::base_calibration_service
  modules::perception::camera::lib::interface::base_calibrator
  modules::perception::camera::lib::interface::base_camera_perception
  modules::perception::camera::lib::interface::base_feature_extractor
  modules::perception::camera::lib::interface::base_inference_engine
  modules::perception::camera::lib::interface::base_init_options
  modules::perception::camera::lib::interface::base_landmark_detector
  modules::perception::camera::lib::interface::base_lane_detector
  modules::perception::camera::lib::interface::base_lane_postprocessor
  modules::perception::camera::lib::interface::base_lane_tracker
  modules::perception::camera::lib::interface::base_obstacle_detector
  modules::perception::camera::lib::interface::base_obstacle_postprocessor
  modules::perception::camera::lib::interface::base_obstacle_tracker
  modules::perception::camera::lib::interface::base_obstacle_transformer
  modules::perception::camera::lib::interface::base_scene_parser
  modules::perception::camera::lib::interface::base_traffic_light_detector
  modules::perception::camera::lib::interface::base_traffic_light_tracker
  modules::perception::camera::lib::interface::base_cipv
  modules::perception::camera::lib::interface::base_tl_preprocessor
)
add_library(modules::perception::camera::lib::interface::interface  ALIAS   modules_perception_camera_lib_interface_interface)

