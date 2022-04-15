#!/usr/bin/env bash

###############################################################################
#  Jiangang Ding Authors. 
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
. ./installer_base.sh


VERSION="20200225.2"
PKG_NAME="abseil-cpp-${VERSION}.tar.gz"
DOWNLOAD_LINK="https://github.com/abseil/abseil-cpp/archive/${VERSION}.tar.gz"


download_if_not_cached "$PKG_NAME" "$CHECKSUM" "$DOWNLOAD_LINK" "${THIRD_PARTY_PATH}"

tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}



pushd ../thirdparty/abseil-cpp-${VERSION}
mkdir build && cd build

cmake .. \
    -DCMAKE_INSTALL_PREFIX=${THIRD_LIBRARY_INSTALL_PATH}/abseil-cpp-20200225.2  \
    -DBUILD_SHARED_LIBS=ON



# ./configure --prefix=/usr
make -j$(nproc)
make install

popd

ok "Successfully installed eigen, VERSION=${VERSION}"

# Clean up.
rm -fr ${THIRD_PARTY_PATH}/${PKG_NAME}


