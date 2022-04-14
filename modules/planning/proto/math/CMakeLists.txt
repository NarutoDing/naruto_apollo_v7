cmake_minimum_required(VERSION 3.16)

project(modules_planning_proto_math)
message("${Green} [info] modules_planning_proto_math cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/planning/proto/math/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_planning_proto_math_fem_pos_deviation_smoother_config_cc_proto  SHARED
  fem_pos_deviation_smoother_config.pb.cc
)
set_target_properties(modules_planning_proto_math_fem_pos_deviation_smoother_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::math::fem_pos_deviation_smoother_config_cc_proto  ALIAS   modules_planning_proto_math_fem_pos_deviation_smoother_config_cc_proto)

add_library(modules_planning_proto_math_cos_theta_smoother_config_cc_proto  SHARED
  cos_theta_smoother_config.pb.cc
)
set_target_properties(modules_planning_proto_math_cos_theta_smoother_config_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::math::cos_theta_smoother_config_cc_proto  ALIAS   modules_planning_proto_math_cos_theta_smoother_config_cc_proto)

add_library(modules_planning_proto_math_qp_problem_cc_proto  SHARED
  qp_problem.pb.cc
)
set_target_properties(modules_planning_proto_math_qp_problem_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)

add_library(modules::planning::proto::math::qp_problem_cc_proto  ALIAS   modules_planning_proto_math_qp_problem_cc_proto)

