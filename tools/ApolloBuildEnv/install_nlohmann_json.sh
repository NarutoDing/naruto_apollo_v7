#!/usr/bin/env bash

###############################################################################
#  Jiangang Ding Authors. 
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
. ./installer_base.sh


VERSION="3.8.0"
PKG_NAME="v${VERSION}.tar.gz"
DOWNLOAD_LINK="https://github.com/nlohmann/json/archive/v${VERSION}.tar.gz"


download_if_not_cached "$PKG_NAME" "$CHECKSUM" "$DOWNLOAD_LINK" "${THIRD_PARTY_PATH}"

tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}



pushd ../thirdparty/json-3.8.0
mkdir build && cd build

cmake .. 
cmake --build .

popd

cp -r ${THIRD_PARTY_PATH}/json-3.8.0 ${NARUTO_APOLLO_ROOT}/bin/library

ok "Successfully installed json, VERSION=${VERSION}"

# Clean up.
rm -fr ${THIRD_PARTY_PATH}/${PKG_NAME}


