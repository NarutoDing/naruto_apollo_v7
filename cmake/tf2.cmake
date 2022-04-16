# Finds  tf2 and compilers and extends
include_directories($ENV{THIRD_LIBRARY_INSTALL_PATH}/tf2/include)
set(third_party::tf2::tf2 $ENV{THIRD_LIBRARY_INSTALL_PATH}/tf2/lib/libtf2.so)



