cmake_minimum_required(VERSION 3.16)

project(modules_common_math_qp_solver)
message("${Green} [info] modules_common_math_qp_solver cmakelist ${ColourReset}")

add_library(modules_common_math_qp_solver_qp_solver  SHARED
  qp_solver.cc
)
set_target_properties(modules_common_math_qp_solver_qp_solver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_common_math_qp_solver_qp_solver
  ${eigen}
)
add_library(modules::common::math::qp_solver::qp_solver  ALIAS   modules_common_math_qp_solver_qp_solver)

