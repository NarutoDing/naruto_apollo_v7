cmake_minimum_required(VERSION 3.16)

project(cyber_python_internal)
message("${Green} [info] cyber_python_internal cmakelist ${ColourReset}")

add_library(cyber_python_internal_py_cyber  SHARED
  py_cyber.cc
)
set_target_properties(cyber_python_internal_py_cyber  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_python_internal_py_cyber
  cyber::cyber_core
  
  ${python_lib}
)
add_library(cyber::python::internal::py_cyber  ALIAS   cyber_python_internal_py_cyber)

add_library(cyber_python_internal_py_record  SHARED
  py_record.cc
)
set_target_properties(cyber_python_internal_py_record  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_python_internal_py_record
  cyber::cyber_core
  cyber::message::py_message
  cyber::record::record
  
  ${python_lib}
)
add_library(cyber::python::internal::py_record  ALIAS   cyber_python_internal_py_record)

add_library(cyber_python_internal_py_time  SHARED
  py_time.cc
)
set_target_properties(cyber_python_internal_py_time  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_python_internal_py_time
  cyber::cyber_core
  ${fastrtps_LIB_DIR}/libfastrtps.so
  
  ${python_lib}
)
add_library(cyber::python::internal::py_time  ALIAS   cyber_python_internal_py_time)

add_library(cyber_python_internal_py_timer  SHARED
  py_timer.cc
)
set_target_properties(cyber_python_internal_py_timer  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_python_internal_py_timer
  cyber::cyber_core
  
  ${python_lib}
)
add_library(cyber::python::internal::py_timer  ALIAS   cyber_python_internal_py_timer)

add_library(cyber_python_internal_py_parameter  SHARED
  py_parameter.cc
)
set_target_properties(cyber_python_internal_py_parameter  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_python_internal_py_parameter
  cyber::python::internal::py_cyber
  cyber::cyber_core
  
  ${python_lib}
)
add_library(cyber::python::internal::py_parameter  ALIAS   cyber_python_internal_py_parameter)

add_library(_cyber_wrapper  SHARED
  py_cyber.cc
)
set_target_properties(_cyber_wrapper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(_cyber_wrapper
  cyber::python::internal::py_cyber
)
add_library(_cyber_record_wrapper  SHARED
  py_record.cc
)
set_target_properties(_cyber_record_wrapper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(_cyber_record_wrapper
  cyber::python::internal::py_record
)
add_library(_cyber_time_wrapper  SHARED
  py_time.cc
)
set_target_properties(_cyber_time_wrapper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(_cyber_time_wrapper
  cyber::python::internal::py_time
)
add_library(_cyber_timer_wrapper  SHARED
  py_timer.cc
)
set_target_properties(_cyber_timer_wrapper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(_cyber_timer_wrapper
  cyber::python::internal::py_timer
)
add_library(_cyber_parameter_wrapper  SHARED
  py_parameter.cc
)
set_target_properties(_cyber_parameter_wrapper  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(_cyber_parameter_wrapper
  cyber::python::internal::py_parameter
)
