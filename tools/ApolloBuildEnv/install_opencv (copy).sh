#!/usr/bin/env bash

###############################################################################
# Copyright 2020 The Apollo Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################
# Fail on first error.
set -e

CURR_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
. ${CURR_DIR}/installer_base.sh

if ldconfig -p | grep -q libopencv_core; then
    info "OpenCV was already installed"
    exit 0
fi

WORKHORSE="$1"
if [ -z "${WORKHORSE}" ]; then
    WORKHORSE="cpu"
fi

# Note(all): opencv_contrib is not required in cpu mode
BUILD_CONTRIB="no"

# 1) Install OpenCV via apt
# apt-get -y update && \
#    apt-get -y install \
#    libopencv-core-dev \
#    libopencv-imgproc-dev \
#    libopencv-imgcodecs-dev \
#    libopencv-highgui-dev \
#    libopencv-dev
# 2) Build OpenCV from source
# RTFM: https://src.fedoraproject.org/rpms/opencv/blob/master/f/opencv.spec

apt_get_update_and_install \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libgtk2.0-dev \
    libv4l-dev \
    libeigen3-dev \
    libopenblas-dev \
    libatlas-base-dev \
    libxvidcore-dev \
    libx264-dev \
    libopenni-dev \
    libwebp-dev

pip3_install numpy

VERSION="4.4.0"

PKG_OCV="opencv-${VERSION}.tar.gz"
CHECKSUM="bb95acd849e458be7f7024d17968568d1ccd2f0681d47fd60d34ffb4b8c52563"
DOWNLOAD_LINK="https://github.com/opencv/opencv/archive/${VERSION}.tar.gz"
download_if_not_cached "${PKG_OCV}" "${CHECKSUM}" "${DOWNLOAD_LINK}"
tar xzf ${PKG_OCV}

# https://stackoverflow.com/questions/12427928/configure-and-build-opencv-to-custom-ffmpeg-install
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${SYSROOT_DIR}/lib
# export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:${SYSROOT_DIR}/lib/pkgconfig
# export PKG_CONFIG_LIBDIR=$PKG_CONFIG_LIBDIR:${SYSROOT_DIR}/lib

# libgtk-3-dev libtbb2 libtbb-dev
# -DWITH_GTK=ON -DWITH_TBB=ON

GPU_OPTIONS=
if [ "${WORKHORSE}" = "gpu" ]; then
    GPU_OPTIONS="-DWITH_CUDA=ON -DWITH_CUFFT=ON -DWITH_CUBLAS=ON -DWITH_CUDNN=ON"
    GPU_OPTIONS="${GPU_OPTIONS} -DCUDA_PROPAGATE_HOST_FLAGS=OFF"
    GPU_OPTIONS="${GPU_OPTIONS} -DCUDA_ARCH_BIN=${SUPPORTED_NVIDIA_SMS// /,}"
    # GPU_OPTIONS="${GPU_OPTIONS} -DWITH_NVCUVID=ON"
    BUILD_CONTRIB="yes"
else
    GPU_OPTIONS="-DWITH_CUDA=OFF"
fi

if [ "${BUILD_CONTRIB}" = "yes" ]; then
    FACE_MODEL_DATA="face_landmark_model.dat"
    CHECKSUM="eeab592db2861a6c94d592a48456cf59945d31483ce94a6bc4d3a4e318049ba3"
    DOWNLOAD_LINK="https://raw.githubusercontent.com/opencv/opencv_3rdparty/8afa57abc8229d611c4937165d20e2a2d9fc5a12/${FACE_MODEL_DATA}"
    download_if_not_cached "${FACE_MODEL_DATA}" "${CHECKSUM}" "${DOWNLOAD_LINK}"

    PKG_CONTRIB="opencv_contrib-${VERSION}.tar.gz"
    CHECKSUM="a69772f553b32427e09ffbfd0c8d5e5e47f7dab8b3ffc02851ffd7f912b76840"
    DOWNLOAD_LINK="https://github.com/opencv/opencv_contrib/archive/${VERSION}.tar.gz"
    download_if_not_cached "${PKG_CONTRIB}" "${CHECKSUM}" "${DOWNLOAD_LINK}"
    tar xzf ${PKG_CONTRIB}

    sed -i "s|https://raw.githubusercontent.com/opencv/opencv_3rdparty/.*|file://${CURR_DIR}/\"|g" \
        opencv_contrib-${VERSION}/modules/face/CMakeLists.txt
fi

TARGET_ARCH="$(uname -m)"

EXTRA_OPTIONS=
if [ "${TARGET_ARCH}" = "x86_64" ]; then
    EXTRA_OPTIONS="${EXTRA_OPTIONS} -DCPU_BASELINE=SSE4"
fi

if [ "${BUILD_CONTRIB}" = "yes" ]; then
    EXTRA_OPTIONS="${EXTRA_OPTIONS} -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-${VERSION}/modules"
else
    EXTRA_OPTIONS="${EXTRA_OPTIONS} -DBUILD_opencv_world=OFF"
fi

# -DBUILD_LIST=core,highgui,improc
pushd "opencv-${VERSION}"
    [[ ! -e build ]] && mkdir build
    pushd build
        cmake .. \
            -DCMAKE_INSTALL_PREFIX="${SYSROOT_DIR}" \
            -DCMAKE_BUILD_TYPE=Release \
            -DBUILD_SHARED_LIBS=ON \
            -DENABLE_PRECOMPILED_HEADERS=OFF \
            -DOPENCV_GENERATE_PKGCONFIG=ON \
            -DBUILD_EXAMPLES=OFF \
            -DBUILD_DOCS=OFF \
            -DBUILD_TESTS=OFF \
            -DBUILD_PERF_TESTS=OFF \
            -DBUILD_JAVA=OFF \
            -DBUILD_PROTOBUF=OFF \
            -DPROTOBUF_UPDATE_FILES=ON \
            -DINSTALL_C_EXAMPLES=OFF \
            -DWITH_QT=OFF \
            -DWITH_GTK=ON \
            -DWITH_GTK_2_X=ON \
            -DWITH_IPP=OFF \
            -DWITH_ITT=OFF \
            -DWITH_TBB=OFF \
            -DWITH_EIGEN=ON \
            -DWITH_FFMPEG=ON \
            -DWITH_LIBV4L=ON \
            -DWITH_OPENMP=ON \
            -DWITH_OPENNI=ON \
            -DWITH_OPENCL=ON \
            -DWITH_WEBP=ON \
            -DOpenGL_GL_PREFERENCE=GLVND \
            -DBUILD_opencv_python2=OFF \
            -DBUILD_opencv_python3=ON \
            -DBUILD_NEW_PYTHON_SUPPORT=ON \
            -DPYTHON_DEFAULT_EXECUTABLE="$(which python3)" \
            -DOPENCV_PYTHON3_INSTALL_PATH="/usr/local/lib/python$(py3_version)/dist-packages" \
            -DOPENCV_ENABLE_NONFREE=ON \
            -DCV_TRACE=OFF \
            ${GPU_OPTIONS} \
            ${EXTRA_OPTIONS}
        make -j$(nproc)
        make install
    popd
popd

ldconfig
ok "Successfully installed OpenCV ${VERSION}."

rm -rf opencv*
if [[ "${BUILD_CONTRIB}" == "yes" ]]; then
    rm -rf ${CURR_DIR}/${FACE_MODEL_DATA}
fi

if [[ -n "${CLEAN_DEPS}" ]]; then
    apt_get_remove \
        libjpeg-dev \
        libpng-dev \
        libtiff-dev \
        libv4l-dev \
        libeigen3-dev \
        libopenblas-dev \
        libatlas-base-dev \
        libxvidcore-dev \
        libx264-dev \
        libgtk2.0-dev \
        libopenni-dev
    apt_get_update_and_install libgtk2.0-0
fi
