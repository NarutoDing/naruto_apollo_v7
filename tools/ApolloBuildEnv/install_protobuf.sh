#!/usr/bin/env bash

###############################################################################
#  Jiangang Ding Authors. 
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
. ./installer_base.sh

if grep -rl protobuf ${THIRD_PARTY_PATH}; then
    info "protobuf was already installed"
    exit 0
else
    info "protobuf was not installed, start to install......"
fi

# Notes on Protobuf Installer:
# 1) protobuf for cpp didn't need to be pre-installed into system
# 2) protobuf for python should be provided for cyber testcases

VERSION="3.14.0"

PKG_NAME="protobuf-${VERSION}.tar.gz"
CHECKSUM="d0f5f605d0d656007ce6c8b5a82df3037e1d8fe8b121ed42e536f569dec16113"
DOWNLOAD_LINK="https://github.com/protocolbuffers/protobuf/archive/v${VERSION}.tar.gz"

#PKG_NAME="protobuf-cpp-${VERSION}.tar.gz"
#CHECKSUM="4ef97ec6a8e0570d22ad8c57c99d2055a61ea2643b8e1a0998d2c844916c4968"
#DOWNLOAD_LINK="https://github.com/protocolbuffers/protobuf/releases/download/v${VERSION}/protobuf-cpp-${VERSION}.tar.gz"

download_if_not_cached "$PKG_NAME" "$CHECKSUM" "$DOWNLOAD_LINK" "${THIRD_PARTY_PATH}"

tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}

# https://developers.google.com/protocol-buffers/docs/reference/python-generated#cpp_impl
export PROTOCOL_BUFFERS_PYTHON_IMPLEMENTATION=cpp

pushd ../thirdparty/protobuf-${VERSION}
mkdir cmake/build && cd cmake/build

cmake .. \
    -DBUILD_SHARED_LIBS=ON \
    -Dprotobuf_BUILD_TESTS=OFF \
    -DCMAKE_INSTALL_PREFIX:PATH="${THIRD_LIBRARY_INSTALL_PATH}/protobuf-${VERSION}" \
    -DCMAKE_BUILD_TYPE=Release

# ./configure --prefix=/usr
make -j$(nproc)
make install

popd

ok "Successfully installed protobuf, VERSION=${VERSION}"

# Clean up.
rm -fr ${THIRD_PARTY_PATH}/${PKG_NAME}
