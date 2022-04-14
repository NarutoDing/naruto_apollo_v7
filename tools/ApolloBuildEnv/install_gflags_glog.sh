#!/usr/bin/env bash

###############################################################################
#  Jiangang Ding Authors. 
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
. ./installer_base.sh

ARCH=$(uname -m)
THREAD_NUM=$(nproc)

# Install gflags.
VERSION="2.2.2"
CHECKSUM="34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf"
PKG_NAME="gflags-${VERSION}.tar.gz"
DOWNLOAD_LINK="https://github.com/gflags/gflags/archive/v${VERSION}.tar.gz"

download_if_not_cached "$PKG_NAME" "$CHECKSUM" "$DOWNLOAD_LINK" "${THIRD_PARTY_PATH}"

tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}

pushd ../thirdparty/gflags-${VERSION}
    mkdir build && cd build
    cmake .. -DBUILD_SHARED_LIBS=ON \
             -DCMAKE_BUILD_TYPE=Release \
             -DCMAKE_INSTALL_PREFIX="${THIRD_LIBRARY_INSTALL_PATH}/gflags-${VERSION}"
    make -j$(nproc)
    make install
popd



# cleanup
rm -fr ${THIRD_PARTY_PATH}/${PKG_NAME}

# Install glog which also depends on gflags.

VERSION="0.4.0"
PKG_NAME="glog-${VERSION}.tar.gz"
CHECKSUM="f28359aeba12f30d73d9e4711ef356dc842886968112162bc73002645139c39c"
DOWNLOAD_LINK="https://github.com/google/glog/archive/v${VERSION}.tar.gz"
# https://github.com/google/glog/archive/v0.4.0.tar.gz

download_if_not_cached "$PKG_NAME" "$CHECKSUM" "$DOWNLOAD_LINK" "${THIRD_PARTY_PATH}"

tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}

pushd ../thirdparty/glog-${VERSION}
    mkdir build && cd build
    cmake .. \
        -DBUILD_SHARED_LIBS=ON \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="${THIRD_LIBRARY_INSTALL_PATH}/glog-${VERSION}"
    # if [ "$ARCH" == "aarch64" ]; then
    #    ./configure --build=armv8-none-linux --enable-shared
    # fi

    make -j$(nproc)
    make install
popd



# clean up.
rm -fr ${THIRD_PARTY_PATH}/${PKG_NAME}
