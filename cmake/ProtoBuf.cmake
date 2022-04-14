# Finds Google Protocol Buffers library and compilers and extends
# the standard cmake script with version and python generation support
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/protobuf-3.14.0/lib/cmake/protobuf/protobuf-config.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/protobuf-3.14.0/lib/cmake/protobuf/protobuf-module.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/protobuf-3.14.0/lib/cmake/protobuf/protobuf-options.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/protobuf-3.14.0/lib/cmake/protobuf/protobuf-targets.cmake)
find_package(Protobuf REQUIRED HINTS  $ENV{THIRD_LIBRARY_INSTALL_PATH}/protobuf-3.14.0/lib/cmake/protobuf)
if(Protobuf_FOUND)
    # fetches protobuf version
  message("${BoldCyan} [ok] protobuf library found ${ColourReset}")
  message(STATUS "Protobuf version : ${Protobuf_VERSION}")
  message(STATUS "Protobuf include path : ${Protobuf_INCLUDE_DIRS}")
  message(STATUS "Protobuf libraries : ${Protobuf_LIBRARIES}")
  message(STATUS "Protobuf compiler libraries : ${Protobuf_PROTOC_LIBRARIES}")
  if(NOT ${Protobuf_VERSION} STREQUAL "3.14.0.0")
    message(FATAL_ERROR "${Red} [error] naruto apollo need 3.14.0.0 protobuf version ${ColourReset}")
  endif()
else()
  message(FATAL_ERROR "${Red} [error] protobuf library is needed but can not be found ${ColourReset}")
endif()
include_directories(${PROTOBUF_INCLUDE_DIRS})

if(EXISTS ${PROTOBUF_PROTOC_EXECUTABLE})
  message(STATUS "Found PROTOBUF Compiler: ${PROTOBUF_PROTOC_EXECUTABLE}")
else()
  message(FATAL_ERROR "Could not find PROTOBUF Compiler")
endif()

set(PROTOBUF_GENERATE_CPP_APPEND_PATH TRUE)

################################################################################################
function(naruto_apollo_protobuf_generate_cpp_py output_dir srcs_var hdrs_var python_var)
  message("${Green} [info] start to generate cpp and python protobuf in ${output_dir} ${ColourReset}")
  if(NOT ARGN)
    message(SEND_ERROR "Error: naruto_apollo_protobuf_generate_cpp_py() called without any proto files")
    return()
  endif()

  if(PROTOBUF_GENERATE_CPP_APPEND_PATH)
    # Create an include path for each file specified
    foreach(fil ${ARGN})
      
      get_filename_component(abs_fil ${fil} ABSOLUTE)
      get_filename_component(abs_path ${abs_fil} PATH)
    endforeach()
  endif()

  if(DEFINED PROTOBUF_IMPORT_DIRS)
    foreach(dir ${PROTOBUF_IMPORT_DIRS})
      get_filename_component(abs_path ${dir} ABSOLUTE)
    endforeach()
  endif()

  set(${srcs_var})
  set(${hdrs_var})
  set(${python_var})
  foreach(fil ${ARGN})
    get_filename_component(abs_fil ${fil} ABSOLUTE)
    get_filename_component(fil_we ${fil} NAME_WE)
    
    list(APPEND ${srcs_var} "${output_dir}/${fil_we}.pb.cc")
    list(APPEND ${hdrs_var} "${output_dir}/${fil_we}.pb.h")
    list(APPEND ${python_var} "${output_dir}/${fil_we}_pb2.py")
    add_custom_command(
      OUTPUT "${output_dir}/${fil_we}.pb.cc"
             "${output_dir}/${fil_we}.pb.h"
             "${output_dir}/${fil_we}_pb2.py"
      COMMAND ${CMAKE_COMMAND} -E make_directory "${output_dir}"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I$ENV{NARUTO_APOLLO_ROOT} --cpp_out=$ENV{NARUTO_APOLLO_ROOT}  ${abs_fil} 
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I$ENV{NARUTO_APOLLO_ROOT} --python_out=$ENV{NARUTO_APOLLO_ROOT}  ${abs_fil} #/home/naruto/naruto_apollo_v7 ${_protoc_include}
      DEPENDS ${abs_fil}
      COMMENT "Running C++/Python protocol buffer compiler on ${fil}" VERBATIM )
  endforeach()
  set_source_files_properties(${${srcs_var}} ${${hdrs_var}} ${${python_var}} PROPERTIES GENERATED TRUE)
  set(${srcs_var} ${${srcs_var}} PARENT_SCOPE)
  set(${hdrs_var} ${${hdrs_var}} PARENT_SCOPE)
  set(${python_var} ${${python_var}} PARENT_SCOPE)
endfunction()
