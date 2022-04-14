#!/usr/bin/env bash

###############################################################################
# Jiangang Ding Authors. 
###############################################################################
# Fail on first error.
set -e

CURR_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
. ${CURR_DIR}/installer_base.sh

#if there is opencv lib, then exit this shell, not to install opencv
if grep -rl libopencv_core ${THIRD_PARTY_PATH}; then
    info "OpenCV was already installed"
    #exit 0
else
    info "OpenCV was not installed, start to install......"
fi

#set opencv version
VERSION="4.4.0"
BUILD_CONTRIB="no"
#opencv package name
PKG_OCV="opencv-${VERSION}.tar.gz"

#checksum
CHECKSUM="bb95acd849e458be7f7024d17968568d1ccd2f0681d47fd60d34ffb4b8c52563"

#download network address
DOWNLOAD_LINK="https://github.com/opencv/opencv/archive/${VERSION}.tar.gz"

#to run download_if_not_cached in installer_base.sh file
#download_if_not_cached "${PKG_OCV}" "${CHECKSUM}" "${DOWNLOAD_LINK}" "${THIRD_PARTY_PATH}"

#to tar PKG_OCV
#tar xzf ${THIRD_PARTY_PATH}/${PKG_OCV} -C ${THIRD_PARTY_PATH}


#to use the follow gpu option to compile opencv
#WORKHORSE is defined in the ApolloEnvHostLinux.sh file	
GPU_OPTIONS=
if [ "${WORKHORSE}" = "gpu" ]; then
    GPU_OPTIONS="-DWITH_CUDA=ON -DWITH_CUFFT=ON -DWITH_CUBLAS=ON -DWITH_CUDNN=ON"
    GPU_OPTIONS="${GPU_OPTIONS} -DCUDA_PROPAGATE_HOST_FLAGS=OFF"
    GPU_OPTIONS="${GPU_OPTIONS} -DCUDA_ARCH_BIN=${SUPPORTED_NVIDIA_SMS// /,}"
    # GPU_OPTIONS="${GPU_OPTIONS} -DWITH_NVCUVID=ON"
    BUILD_CONTRIB="yes"
    info "gpu options is: " ${GPU_OPTIONS}
else
    GPU_OPTIONS="-DWITH_CUDA=OFF"
fi

if [ "${BUILD_CONTRIB}" = "yes" ]; then
    FACE_MODEL_DATA="face_landmark_model.dat"
    CHECKSUM="eeab592db2861a6c94d592a48456cf59945d31483ce94a6bc4d3a4e318049ba3"
    DOWNLOAD_LINK="https://raw.githubusercontent.com/opencv/opencv_3rdparty/8afa57abc8229d611c4937165d20e2a2d9fc5a12/${FACE_MODEL_DATA}"
    download_if_not_cached "${FACE_MODEL_DATA}" "${CHECKSUM}" "${DOWNLOAD_LINK}" "${THIRD_PARTY_PATH}"

    PKG_CONTRIB="opencv_contrib-${VERSION}.tar.gz"
    CHECKSUM="a69772f553b32427e09ffbfd0c8d5e5e47f7dab8b3ffc02851ffd7f912b76840"
    DOWNLOAD_LINK="https://github.com/opencv/opencv_contrib/archive/${VERSION}.tar.gz"
    download_if_not_cached "${PKG_CONTRIB}" "${CHECKSUM}" "${DOWNLOAD_LINK}" "${THIRD_PARTY_PATH}"
    tar xzf ${THIRD_PARTY_PATH}/${PKG_CONTRIB} -C ${THIRD_PARTY_PATH}

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
pushd ../thirdparty/"opencv-${VERSION}"
    [[ ! -e build ]] && mkdir build
    pushd build
        cmake .. \
            -DCMAKE_INSTALL_PREFIX="${THIRD_PARTY_PATH}/opencv-${VERSION}" \
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
            #-DPYTHON_DEFAULT_EXECUTABLE="$(which python3.9)" \
            #-DOPENCV_PYTHON3_INSTALL_PATH="/usr/local/lib/python$(py3_version)/dist-packages" \
            -DOPENCV_ENABLE_NONFREE=ON \
            -DCV_TRACE=OFF \
            ${GPU_OPTIONS} \
            ${EXTRA_OPTIONS}
        make -j$(nproc)
        make install
    popd
popd
