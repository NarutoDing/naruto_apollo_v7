cmake_minimum_required(VERSION 3.16)

project(modules_thirdparty_rtklib)
message("${Green} [info] modules_thirdparty_rtklib cmakelist ${ColourReset}")

add_library(modules_thirdparty_rtklib  SHARED
  novatel.c
  rcvraw.c
  rtcm.c
  rtcm3.c
  rtkcmn.c
)
set_target_properties(modules_thirdparty_rtklib  PROPERTIES LINKER_LANGUAGE CXX)
add_library(third_party::rtklib::rtklib  ALIAS   modules_thirdparty_rtklib)

