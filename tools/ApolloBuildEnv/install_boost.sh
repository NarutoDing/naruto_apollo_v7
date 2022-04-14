#!/usr/bin/env bash

###############################################################################
# Jiangang Ding Authors. 
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"
. ./installer_base.sh


#if there is boost lib, then exit this shell, not to install boost
if grep -rl libboost_system.so ${THIRD_PARTY_PATH}; then
    info "Found existing Boost installation. Reinstallation skipped."
    exit 0
else
    info "boost lib was not installed, start to install......"
fi


# PreReq for Unicode support for Boost.Regex
#    icu-devtools \
#    libicu-dev

#apt_get_update_and_install \
#    liblzma-dev \
#    libbz2-dev \
#    libzstd-dev

# Ref: https://www.boost.org/
py3_ver="$(py3_version)"
VERSION="1_74_0"

PKG_NAME="boost_${VERSION}.tar.bz2"
DOWNLOAD_LINK="https://sourceforge.net/projects/boost/files/boost/${VERSION//_/.}/boost_${VERSION}.tar.bz2/download"
#DOWNLOAD_LINK="https://dl.bintray.com/boostorg/release/${VERSION//_/.}/source/boost_${VERSION}.tar.bz2"
CHECKSUM="83bfc1507731a0906e387fc28b7ef5417d591429e51e788417fe9ff025e116b1"

download_if_not_cached "${PKG_NAME}" "${CHECKSUM}" "${DOWNLOAD_LINK}" "${THIRD_PARTY_PATH}"

tar xzf ${THIRD_PARTY_PATH}/${PKG_NAME} -C ${THIRD_PARTY_PATH}
#rm -rf ${THIRD_PARTY_PATH}/${PKG_NAME}

# Ref: https://www.boost.org/doc/libs/1_73_0/doc/html/mpi/getting_started.html
pushd ../thirdparty/"boost_${VERSION}"
    # A) For mpi built from source
    #  echo "using mpi : ${SYSROOT_DIR}/bin/mpicc ;" > user-config.jam
    # B) For mpi installed via apt
    # echo "using mpi ;" > user-config.jam
    ./bootstrap.sh \
        --with-python-version=${py3_ver} \
        --prefix="${SYSROOT_DIR}" \
        --without-icu

    ./b2 -d+2 -q -j$(nproc) \
        --without-graph_parallel \
        --without-mpi \
        variant=release \
        link=shared \
        threading=multi \
        install
        #--user-config=user-config.jam
popd


