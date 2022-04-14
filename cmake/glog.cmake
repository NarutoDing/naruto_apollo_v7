# Finds glog library and compilers and extends
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/glog-0.4.0/lib/cmake/glog/glog-config.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/glog-0.4.0/lib/cmake/glog/glog-config-version.cmake)
if(NOT ${PACKAGE_VERSION} STREQUAL "0.4.0")
  message(FATAL_ERROR "${Red} [error] naruto apollo need glog 0.4.0 ${ColourReset}")
endif()
set(glog_INCLUDE_DIR "$ENV{THIRD_LIBRARY_INSTALL_PATH}/glog-0.4.0/include")
set(glog_LIBRARIES "$ENV{THIRD_LIBRARY_INSTALL_PATH}/glog-0.4.0/lib/libglog.so")
message("${BoldCyan} [ok] glog library found ${ColourReset}")
message(STATUS "glog version : ${PACKAGE_VERSION}")
message(STATUS "glog include path : ${glog_INCLUDE_DIR}")
message(STATUS "glog libraries : ${glog_LIBRARIES}")

include_directories(${glog_INCLUDE_DIR})

