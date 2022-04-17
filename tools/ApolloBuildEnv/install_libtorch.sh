#!/usr/bin/env bash

###############################################################################
#  Jiangang Ding Authors. 
###############################################################################

# Fail on first error.

set -e

CURR_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
. ${CURR_DIR}/installer_base.sh

#bash ${CURR_DIR}/install_mkl.sh

TARGET_ARCH="$(uname -m)"

##============================================================##
# libtorch_cpu

if [[ "${TARGET_ARCH}" == "x86_64" ]]; then
    # https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.5.0%2Bcpu.zip
    VERSION="1.7.0-2"
    CHECKSUM="02fd4f30e97ce8911ef933d0516660892392e95e6768b50f591f4727f6224390"
elif [[ "${TARGET_ARCH}" == "aarch64" ]]; then
    VERSION="1.6.0-1"
    CHECKSUM="6d1fba522e746213c209fbf6275fa6bac68e360bcd11cbd4d3bdbddb657bee82"
else
    error "libtorch for ${TARGET_ARCH} not ready. Exiting..."
    exit 1
fi

PKG_NAME="libtorch_cpu-${VERSION}-linux-${TARGET_ARCH}.tar.gz"
DOWNLOAD_LINK="https://apollo-system.cdn.bcebos.com/archive/6.0/${PKG_NAME}"
download_if_not_cached "$PKG_NAME" "$CHECKSUM" "$DOWNLOAD_LINK" "${THIRD_PARTY_PATH}"

echo ${PKG_NAME}
tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}
cp -r ${THIRD_PARTY_PATH}/libtorch_cpu-${VERSION}-linux-${TARGET_ARCH} ${NARUTO_APOLLO_ROOT}/bin/library 
#mv "${PKG_NAME%.tar.gz}" /usr/local/libtorch_cpu
rm -f "${THIRD_PARTY_PATH}/${PKG_NAME}"
ok "Successfully installed libtorch_cpu ${VERSION}"

##============================================================##
# libtorch_gpu
if [[ "${TARGET_ARCH}" == "x86_64" ]]; then
    VERSION="1.7.0-2"
    CHECKSUM="b64977ca4a13ab41599bac8a846e8782c67ded8d562fdf437f0e606cd5a3b588"
    PKG_NAME="libtorch_gpu-${VERSION}-cu111-linux-x86_64.tar.gz"
else # AArch64
    VERSION="1.6.0-1"
    PKG_NAME="libtorch_gpu-1.6.0-1-linux-aarch64.tar.gz"
    CHECKSUM="eeb5a223d9dbe40fe96f16e6711c49a3777cea2c0a8da2445d63e117fdad0385"
fi

DOWNLOAD_LINK="https://apollo-system.cdn.bcebos.com/archive/6.0/${PKG_NAME}"
download_if_not_cached "$PKG_NAME" "$CHECKSUM" "$DOWNLOAD_LINK" "${THIRD_PARTY_PATH}"

tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}
cp -r ${THIRD_PARTY_PATH}/libtorch_gpu-${VERSION}-cu111-linux-x86_64 ${NARUTO_APOLLO_ROOT}/bin/library 
# Cleanup
rm -f "${THIRD_PARTY_PATH}/${PKG_NAME}"
ok "Successfully installed libtorch_gpu ${VERSION}"
