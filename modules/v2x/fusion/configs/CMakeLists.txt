cmake_minimum_required(VERSION 3.16)

project(modules_v2x_fusion_configs)
message("${Green} [info] modules_v2x_fusion_configs cmakelist ${ColourReset}")

add_library(modules_v2x_fusion_configs_fusion_tracker_gflags  SHARED
  fusion_tracker_gflags.cc
)
set_target_properties(modules_v2x_fusion_configs_fusion_tracker_gflags  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_fusion_configs_fusion_tracker_gflags
  ${gflags_LIBRARIES}
)
add_library(modules::v2x::fusion::configs::fusion_tracker_gflags  ALIAS   modules_v2x_fusion_configs_fusion_tracker_gflags)

add_library(modules_v2x_fusion_configs_ft_config_manager  SHARED
  ft_config_manager.cc
)
set_target_properties(modules_v2x_fusion_configs_ft_config_manager  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_v2x_fusion_configs_ft_config_manager
  modules::v2x::fusion::configs::fusion_tracker_gflags
  cyber::cyber
  modules::v2x::proto::fusion_params_cc_proto
  ${boost}
)
add_library(modules::v2x::fusion::configs::ft_config_manager  ALIAS   modules_v2x_fusion_configs_ft_config_manager)

