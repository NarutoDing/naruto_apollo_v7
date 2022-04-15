#!/usr/bin/env bash

###############################################################################
#  Jiangang Ding Authors. 
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
. ./installer_base.sh


VERSION="1.11"
PKG_NAME="v${VERSION}.tar.gz"
DOWNLOAD_LINK="https://github.com/civetweb/civetweb/archive/v${VERSION}.tar.gz"


download_if_not_cached "$PKG_NAME" "$CHECKSUM" "$DOWNLOAD_LINK" "${THIRD_PARTY_PATH}"

tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}


cp -r ${THIRD_PARTY_PATH}/civetweb-1.11 ${NARUTO_APOLLO_ROOT}/modules


ok "Successfully installed civetweb, VERSION=${VERSION}"

# Clean up.
rm -fr ${THIRD_PARTY_PATH}/${PKG_NAME}


