#!/usr/bin/env bash

###############################################################################
# Jiangang Ding Authors. 
###############################################################################


set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
. ./installer_base.sh

TARGET_ARCH="$(uname -m)"

#apt_get_update_and_install \
#    libasio-dev \
#    libtinyxml2-dev

# Note(storypku)
# 1) More recent Fast-DDS (formerly Fast-RTPS) implementations:
# Ref: https://github.com/eProsima/Fast-DDS
# Ref: https://github.com/ros2/rmw_fastrtps
# 2) How to create the diff
# git diff --submodule=diff > /tmp/FastRTPS_1.5.0.patch
# Ref: https://stackoverflow.com/questions/10757091/git-list-of-all-changed-files-including-those-in-submodules

if [[ "${INSTALL_MODE}" == "build" ]]; then
    git clone --single-branch --branch release/1.5.0 --depth 1 https://github.com/eProsima/Fast-RTPS.git "${THIRD_PARTY_PATH}/Fast-RTPS"
    pushd ../thirdparty/Fast-RTPS
        git submodule update --init
        patch -p1 < ../FastRTPS_1.5.0.patch

        mkdir -p build && cd build
        cmake -DEPROSIMA_BUILD=ON \
            -DCMAKE_BUILD_TYPE=Release \
            -DCMAKE_INSTALL_PREFIX=${THIRD_LIBRARY_INSTALL_PATH}/fast-rtps ..
        make -j$(nproc)
        make install
    popd

    rm -fr ${THIRD_PARTY_PATH}/Fast-RTPS
    exit 0
fi


if [[ "${TARGET_ARCH}" == "x86_64" ]]; then
    PKG_NAME="fast-rtps-1.5.0-1.prebuilt.x86_64.tar.gz"
    CHECKSUM="7f6cd1bee91f3c08149013b3d0d5ff46290fbed17b13a584fe8625d7553f603d"
    DOWNLOAD_LINK="https://apollo-system.cdn.bcebos.com/archive/6.0/${PKG_NAME}"

    download_if_not_cached "${PKG_NAME}" "${CHECKSUM}" "${DOWNLOAD_LINK}" "${THIRD_PARTY_PATH}"
    tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}
    cp -r ${THIRD_PARTY_PATH}/fast-rtps-1.5.0-1 ${THIRD_LIBRARY_INSTALL_PATH}
    rm -rf ${THIRD_PARTY_PATH}/fast-rtps-1.5.0-1
    rm -rf ${THIRD_PARTY_PATH}/${PKG_NAME}
else # aarch64
    PKG_NAME="fast-rtps-1.5.0-1.prebuilt.aarch64.tar.gz"
    CHECKSUM="4c02a60ab114dafecb6bfc9c54bb9250f39fc44529253268138df1abddd5a011"
    DOWNLOAD_LINK="https://apollo-system.cdn.bcebos.com/archive/6.0/${PKG_NAME}"

    download_if_not_cached "${PKG_NAME}" "${CHECKSUM}" "${DOWNLOAD_LINK}" "${THIRD_PARTY_PATH}"
    tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}
    rm -rf ${THIRD_PARTY_PATH}/${PKG_NAME}
fi


