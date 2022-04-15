# Finds  eigen and compilers and extends
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/eigen-git-mirror-3.3.7/share/eigen3/cmake/Eigen3Config.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/eigen-git-mirror-3.3.7/share/eigen3/cmake/Eigen3ConfigVersion.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/eigen-git-mirror-3.3.7/share/eigen3/cmake/Eigen3Targets.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/eigen-git-mirror-3.3.7/share/eigen3/cmake/UseEigen3.cmake)
message("${BoldCyan} [ok] eigen library found ${ColourReset}")
message(STATUS "eigen version : ${EIGEN3_VERSION_STRING}")
message(STATUS "eigen include path : ${EIGEN3_INCLUDE_DIR}")
if(NOT ${PACKAGE_VERSION} STREQUAL "3.3.7")
    message(FATAL_ERROR "${Red} [error] naruto apollo need eigen 3.3.7 ${ColourReset}")
endif()
include_directories(${EIGEN3_INCLUDE_DIR})



