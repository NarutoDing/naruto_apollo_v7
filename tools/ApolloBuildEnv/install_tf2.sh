#!/usr/bin/env bash

###############################################################################
#  Jiangang Ding Authors. 
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
. ./installer_base.sh



pushd ../thirdparty/tf2
mkdir build && cd build

cmake .. \
    -DBUILD_TESTS=OFF \
    -DCMAKE_INSTALL_PREFIX=${THIRD_LIBRARY_INSTALL_PATH}/tf2




# ./configure --prefix=/usr
make -j$(nproc)
make install

popd



