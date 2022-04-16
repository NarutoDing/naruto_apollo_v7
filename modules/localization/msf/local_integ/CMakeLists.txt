cmake_minimum_required(VERSION 3.16)

project(modules_localization_msf_local_integ)
message("${Green} [info] modules_localization_msf_local_integ cmakelist ${ColourReset}")

file(GLOB all_srcs ./*.cc)
add_library(modules_localization_msf_local_integ_local_integ  SHARED
  ${all_srcs}
)
set_target_properties(modules_localization_msf_local_integ_local_integ  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_localization_msf_local_integ_local_integ
  modules::common::math::math
  modules::common::status::status
  modules::common::util::perf_util
  modules::common::util::time_util
  modules::drivers::gnss::proto::gnss_best_pose_cc_proto
  modules::drivers::gnss::proto::gnss_cc_proto
  modules::drivers::gnss::proto::gnss_raw_observation_cc_proto
  modules::drivers::gnss::proto::heading_cc_proto
  modules::drivers::gnss::proto::imu_cc_proto
  modules::drivers::proto::pointcloud_cc_proto
  modules::localization::common::localization_common
  modules::localization::msf::common::util::util
  modules::localization::msf::common::util::frame_transform
  modules::localization::msf::local_pyramid_map::base_map::base_map
  modules::localization::msf::local_pyramid_map::pyramid_map::pyramid_map
  modules::localization::msf::local_pyramid_map::pyramid_map::pyramid_map_pool
  modules::localization::proto::gnss_pnt_result_cc_proto
  modules::localization::proto::localization_cc_proto
  modules::localization::proto::localization_status_cc_proto
  modules::localization::proto::measure_cc_proto
  modules::localization::proto::pose_cc_proto
  modules::localization::proto::sins_pva_cc_proto
  ${localization_msf} #bug
  ${gflags_LIBRARIES}
  ${yaml}
  ${glog_LIBRARIES}
  ${eigen}
  
)
add_library(modules::localization::msf::local_integ::local_integ  ALIAS   modules_localization_msf_local_integ_local_integ)

