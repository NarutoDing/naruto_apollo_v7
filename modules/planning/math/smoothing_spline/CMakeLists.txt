cmake_minimum_required(VERSION 3.16)

project(modules_planning_math_smoothing_spline)
message("${Green} [info] modules_planning_math_smoothing_spline cmakelist ${ColourReset}")

add_library(modules_planning_math_smoothing_spline_affine_constraint  SHARED
  affine_constraint.cc
)
set_target_properties(modules_planning_math_smoothing_spline_affine_constraint  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_affine_constraint
  modules::planning::math::polynomial_xd
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::affine_constraint  ALIAS   modules_planning_math_smoothing_spline_affine_constraint)

add_library(modules_planning_math_smoothing_spline_spline_1d_seg  SHARED
  spline_1d_seg.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_1d_seg  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_1d_seg
  modules::planning::math::polynomial_xd
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_1d_seg  ALIAS   modules_planning_math_smoothing_spline_spline_1d_seg)

add_library(modules_planning_math_smoothing_spline_spline_1d  SHARED
  spline_1d.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_1d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_1d
  modules::planning::math::smoothing_spline::affine_constraint
  modules::planning::math::smoothing_spline::spline_1d_seg
  modules::planning::math::polynomial_xd
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_1d  ALIAS   modules_planning_math_smoothing_spline_spline_1d)

add_library(modules_planning_math_smoothing_spline_spline_1d_constraint  SHARED
  spline_1d_constraint.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_1d_constraint  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_1d_constraint
  modules::planning::math::smoothing_spline::affine_constraint
  modules::planning::math::smoothing_spline::spline_1d
  cyber::common::log
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_1d_constraint  ALIAS   modules_planning_math_smoothing_spline_spline_1d_constraint)

add_library(modules_planning_math_smoothing_spline_spline_seg_kernel  SHARED
  spline_seg_kernel.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_seg_kernel  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_seg_kernel
  cyber::common::log
  cyber::common::macros
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_seg_kernel  ALIAS   modules_planning_math_smoothing_spline_spline_seg_kernel)

add_library(modules_planning_math_smoothing_spline_spline_1d_kernel  SHARED
  spline_1d_kernel.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_1d_kernel  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_1d_kernel
  modules::planning::math::smoothing_spline::affine_constraint
  modules::planning::math::smoothing_spline::spline_1d
  modules::planning::math::smoothing_spline::spline_seg_kernel
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_1d_kernel  ALIAS   modules_planning_math_smoothing_spline_spline_1d_kernel)

add_library(modules_planning_math_smoothing_spline_spline_1d_solver  SHARED
  spline_1d_solver.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_1d_solver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_1d_solver
  modules::planning::math::smoothing_spline::spline_1d
  modules::planning::math::smoothing_spline::spline_1d_constraint
  modules::planning::math::smoothing_spline::spline_1d_kernel
  modules::common::math::qp_solver::qp_solver
  modules::planning::common::planning_gflags
  modules::planning::proto::math::qp_problem_cc_proto
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_1d_solver  ALIAS   modules_planning_math_smoothing_spline_spline_1d_solver)

add_library(modules_planning_math_smoothing_spline_osqp_spline_1d_solver  SHARED
  osqp_spline_1d_solver.cc
)
set_target_properties(modules_planning_math_smoothing_spline_osqp_spline_1d_solver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_osqp_spline_1d_solver
  modules::planning::math::smoothing_spline::spline_1d_solver
  modules::common::math::matrix_operations
  ${eigen}
  ${osqp}
)
add_library(modules::planning::math::smoothing_spline::osqp_spline_1d_solver  ALIAS   modules_planning_math_smoothing_spline_osqp_spline_1d_solver)

add_library(modules_planning_math_smoothing_spline_spline_2d_seg  SHARED
  spline_2d_seg.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_2d_seg  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_2d_seg
  modules::planning::math::polynomial_xd
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_2d_seg  ALIAS   modules_planning_math_smoothing_spline_spline_2d_seg)

add_library(modules_planning_math_smoothing_spline_spline_2d  SHARED
  spline_2d.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_2d  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_2d
  modules::planning::math::smoothing_spline::spline_2d_seg
  modules::planning::math::polynomial_xd
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_2d  ALIAS   modules_planning_math_smoothing_spline_spline_2d)

add_library(modules_planning_math_smoothing_spline_spline_2d_constraint  SHARED
  spline_2d_constraint.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_2d_constraint  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_2d_constraint
  modules::planning::math::smoothing_spline::affine_constraint
  modules::planning::math::smoothing_spline::spline_2d
  modules::common::math::angle
  modules::common::math::geometry
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_2d_constraint  ALIAS   modules_planning_math_smoothing_spline_spline_2d_constraint)

add_library(modules_planning_math_smoothing_spline_spline_2d_kernel  SHARED
  spline_2d_kernel.cc
)
set_target_properties(modules_planning_math_smoothing_spline_spline_2d_kernel  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_2d_kernel
  modules::planning::math::smoothing_spline::spline_2d
  modules::planning::math::smoothing_spline::spline_seg_kernel
  modules::common::math::geometry
  ${eigen}
)
add_library(modules::planning::math::smoothing_spline::spline_2d_kernel  ALIAS   modules_planning_math_smoothing_spline_spline_2d_kernel)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(modules_planning_math_smoothing_spline_spline_2d_solver  SHARED
  ${virtual_cc}
  osqp_spline_2d_solver.h
  spline_2d_solver.h
)
set_target_properties(modules_planning_math_smoothing_spline_spline_2d_solver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_spline_2d_solver
  modules::planning::math::smoothing_spline::spline_2d
  modules::planning::math::smoothing_spline::spline_2d_constraint
  modules::planning::math::smoothing_spline::spline_2d_kernel
  modules::common::math::geometry
  modules::common::math::matrix_operations
  modules::common::math::qp_solver::qp_solver
  modules::planning::common::planning_gflags
  ${eigen}
  ${osqp}
)
add_library(modules::planning::math::smoothing_spline::spline_2d_solver  ALIAS   modules_planning_math_smoothing_spline_spline_2d_solver)

add_library(modules_planning_math_smoothing_spline_osqp_spline_2d_solver  SHARED
  osqp_spline_2d_solver.cc
)
set_target_properties(modules_planning_math_smoothing_spline_osqp_spline_2d_solver  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_planning_math_smoothing_spline_osqp_spline_2d_solver
  modules::planning::math::smoothing_spline::spline_2d_solver
  modules::common::math::matrix_operations
  
  ${osqp}
)
add_library(modules::planning::math::smoothing_spline::osqp_spline_2d_solver  ALIAS   modules_planning_math_smoothing_spline_osqp_spline_2d_solver)

