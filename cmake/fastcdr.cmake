# Finds fastrtps library and compilers and extends
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/fast-rtps-1.5.0-1/lib/fastcdr/cmake/fastcdrConfig.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/fast-rtps-1.5.0-1/lib/fastcdr/cmake/fastcdrConfigVersion.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/fast-rtps-1.5.0-1/lib/fastcdr/cmake/fastcdrTargets.cmake)
find_package(fastcdr REQUIRED HINTS  $ENV{THIRD_LIBRARY_INSTALL_PATH}/fast-rtps-1.5.0-1/lib/fastcdr/cmake)
if(fastcdr_FOUND)
  message("${BoldCyan} [ok] fastcdr library found ${ColourReset}")
  message(STATUS "fastcdr version : ${PACKAGE_VERSION}")
  message(STATUS "fastcdr include path : ${fastcdr_INCLUDE_DIR}")
  message(STATUS "fastcdr libraries : ${fastcdr_LIB_DIR}")
  if(NOT ${PACKAGE_VERSION} STREQUAL "1.0.7")
    message(FATAL_ERROR "${Red} [error] naruto apollo need fastcdr 1.0.7 ${ColourReset}")
  endif()
else()
  message(FATAL_ERROR "${Red} [error] fastcdr is needed but can not be found ${ColourReset}")
endif()
include_directories(${fastcdr_INCLUDE_DIR})

