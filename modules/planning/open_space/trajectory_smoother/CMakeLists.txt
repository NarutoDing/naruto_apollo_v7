cmake_minimum_required(VERSION 3.16)

project(modules_planning_open_space_trajectory_smoother)
message("${Green} [info] modules_planning_open_space_trajectory_smoother cmakelist ${ColourReset}")

add_library(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_problem  SHARED
  dual_variable_warm_start_problem.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_problem  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_problem
  modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_ipopt_interface
  modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_ipopt_qp_interface
  modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_osqp_interface
  modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_slack_osqp_interface
  cyber::common::log
  modules::common::util::perf_util
)
add_library(modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_problem  ALIAS   modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_problem)

add_library(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_ipopt_interface  SHARED
  dual_variable_warm_start_ipopt_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_ipopt_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_ipopt_interface
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${adolc}
  ${eigen}
  ${ipopt}
)
add_library(modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_ipopt_interface  ALIAS   modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_ipopt_interface)

add_library(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_ipopt_qp_interface  SHARED
  dual_variable_warm_start_ipopt_qp_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_ipopt_qp_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_ipopt_qp_interface
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${adolc}
  ${eigen}
  ${ipopt}
)
add_library(modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_ipopt_qp_interface  ALIAS   modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_ipopt_qp_interface)

add_library(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_osqp_interface  SHARED
  dual_variable_warm_start_osqp_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_osqp_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_osqp_interface
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${eigen}
  ${osqp}
)
add_library(modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_osqp_interface  ALIAS   modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_osqp_interface)

add_library(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_slack_osqp_interface  SHARED
  dual_variable_warm_start_slack_osqp_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_slack_osqp_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_slack_osqp_interface
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${eigen}
  ${osqp}
)
add_library(modules::planning::open_space::trajectory_smoother::dual_variable_warm_start_slack_osqp_interface  ALIAS   modules_planning_open_space_trajectory_smoother_dual_variable_warm_start_slack_osqp_interface)

add_library(modules_planning_open_space_trajectory_smoother_distance_approach_problem  SHARED
  distance_approach_problem.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_distance_approach_problem  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_distance_approach_problem
  modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_cuda_interface
  modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_fixed_dual_interface
  modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_fixed_ts_interface
  modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_interface
  modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_relax_end_interface
  modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_relax_end_slack_interface
  cyber::common::log
  modules::common::util::perf_util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
)
add_library(modules::planning::open_space::trajectory_smoother::distance_approach_problem  ALIAS   modules_planning_open_space_trajectory_smoother_distance_approach_problem)

add_library(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_fixed_ts_interface  SHARED
  distance_approach_ipopt_fixed_ts_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_fixed_ts_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_fixed_ts_interface
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${adolc}
  ${eigen}
  ${ipopt}
)
add_library(modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_fixed_ts_interface  ALIAS   modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_fixed_ts_interface)

add_library(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_fixed_dual_interface  SHARED
  distance_approach_ipopt_fixed_dual_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_fixed_dual_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_fixed_dual_interface
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${adolc}
  ${eigen}
  ${ipopt}
)
add_library(modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_fixed_dual_interface  ALIAS   modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_fixed_dual_interface)

add_library(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_relax_end_interface  SHARED
  distance_approach_ipopt_relax_end_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_relax_end_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_relax_end_interface
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${adolc}
  ${eigen}
  ${ipopt}
)
add_library(modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_relax_end_interface  ALIAS   modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_relax_end_interface)

add_library(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_relax_end_slack_interface  SHARED
  distance_approach_ipopt_relax_end_slack_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_relax_end_slack_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_relax_end_slack_interface
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${adolc}
  ${eigen}
  ${ipopt}
)
add_library(modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_relax_end_slack_interface  ALIAS   modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_relax_end_slack_interface)

add_library(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_interface  SHARED
  distance_approach_ipopt_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_interface
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${adolc}
  ${eigen}
  ${ipopt}
)
add_library(modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_interface  ALIAS   modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_interface)

add_library(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_cuda_interface  SHARED
  distance_approach_ipopt_cuda_interface.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_cuda_interface  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_cuda_interface
  cyber::common::log
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::common::util::util
  modules::planning::common::planning_gflags
  modules::planning::proto::planner_open_space_config_cc_proto
  modules::planning::proto::planning_cc_proto
  ${adolc}
  ${eigen}
  ${ipopt}
  
  modules::planning::open_space::trajectory_smoother::planning_block
)
add_library(modules::planning::open_space::trajectory_smoother::distance_approach_ipopt_cuda_interface  ALIAS   modules_planning_open_space_trajectory_smoother_distance_approach_ipopt_cuda_interface)

add_library(modules_planning_open_space_trajectory_smoother_iterative_anchoring_smoother  SHARED
  iterative_anchoring_smoother.cc
)
set_target_properties(modules_planning_open_space_trajectory_smoother_iterative_anchoring_smoother  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_iterative_anchoring_smoother
  modules::common::configs::vehicle_config_helper
  modules::common::math::math
  modules::planning::common::speed_profile_generator
  modules::planning::common::path::discretized_path
  modules::planning::common::speed::speed_data
  modules::planning::common::trajectory::discretized_trajectory
  modules::planning::math::discrete_points_math
  modules::planning::math::discretized_points_smoothing::fem_pos_deviation_smoother
  ${eigen}
)
add_library(modules::planning::open_space::trajectory_smoother::iterative_anchoring_smoother  ALIAS   modules_planning_open_space_trajectory_smoother_iterative_anchoring_smoother)

cuda_add_library(modules_planning_open_space_trajectory_smoother_planning_block
  planning_block.cu
)
set_target_properties(modules_planning_open_space_trajectory_smoother_planning_block  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_open_space_trajectory_smoother_planning_block
  ${cuda}
)
add_library(modules::planning::open_space::trajectory_smoother::planning_block  ALIAS   modules_planning_open_space_trajectory_smoother_planning_block)

