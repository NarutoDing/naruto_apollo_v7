# Finds abseil library and compilers and extends
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/abseil-cpp-20200225.2/lib/cmake/absl/abslConfig.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/abseil-cpp-20200225.2/lib/cmake/absl/abslTargets.cmake)
include($ENV{THIRD_LIBRARY_INSTALL_PATH}/abseil-cpp-20200225.2/lib/cmake/absl/abslTargets-noconfig.cmake)
find_package(absl REQUIRED HINTS  $ENV{THIRD_LIBRARY_INSTALL_PATH}/abseil-cpp-20200225.2/lib/cmake/absl)
if(absl_FOUND)
  message("${BoldCyan} [ok] Abseil library found ${ColourReset}")
  file(GLOB absl $ENV{THIRD_LIBRARY_INSTALL_PATH}/abseil-cpp-20200225.2/lib/*.so)
else()
  message(FATAL_ERROR "${Red} [error] Abseil is needed but can not be found ${ColourReset}")
endif()
include_directories($ENV{THIRD_LIBRARY_INSTALL_PATH}/abseil-cpp-20200225.2/include)


