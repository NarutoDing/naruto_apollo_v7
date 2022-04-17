# Finds  cancard and compilers and extends

include_directories($ENV{THIRD_LIBRARY_INSTALL_PATH}/can_card_library/hermes_can/include)
include_directories($ENV{THIRD_LIBRARY_INSTALL_PATH}/can_card_library)
file(GLOB hermes_can $ENV{THIRD_LIBRARY_INSTALL_PATH}/can_card_library/hermes_can/lib_x86_64/*.so)
file(GLOB esd_can $ENV{THIRD_LIBRARY_INSTALL_PATH}/can_card_library/esd_can/libntcan.so.4.2.3)



