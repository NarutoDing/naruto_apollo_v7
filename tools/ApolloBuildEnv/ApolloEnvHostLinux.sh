#! /bin/sh
#set -x
#set -e

cat << End-of-msg
--------------------------
Welcome to apollo project
I wish you a happy study
--------------------------
End-of-msg
#path setting......
APOLLO_BUILD_ENV_DIR=$PWD

export TOOL_BASE_PATH=$(realpath "$APOLLO_BUILD_ENV_DIR/..")
echo TOOL_BASE_PATH =  $TOOL_BASE_PATH

export NARUTO_APOLLO_ROOT=$(realpath "$TOOL_BASE_PATH/..")
echo NARUTO_APOLLO_ROOT=$(realpath "$TOOL_BASE_PATH/..")

export CMAKE_BIN_PATH="$TOOL_BASE_PATH/Cmake-3.20.5/bin/cmake"
echo CMAKE_BIN_PATH =  $CMAKE_BIN_PATH

export PYTHON_BIN_PATH="$TOOL_BASE_PATH/Python-3.9.5/bin/"
echo PYTHON_BIN_PATH = $PYTHON_BIN_PATH


export THIRD_PARTY_PATH="${TOOL_BASE_PATH}/thirdparty"
echo THIRD_PARTY_PATH = $THIRD_PARTY_PATH

export OpenCV_DIR="$THIRD_PARTY_PATH/opencv-4.4.0"

if [ ! -d "$TOOL_BASE_PATH/../bin" ];then
  mkdir -p $TOOL_BASE_PATH/../bin/cyber
  mkdir -p $TOOL_BASE_PATH/../bin/modules
  mkdir -p $TOOL_BASE_PATH/../bin/library
fi

export CYBER_INSTALL_PATH=$TOOL_BASE_PATH/../bin/cyber
echo CYBER_INSTALL_PATH = $TOOL_BASE_PATH/../bin/cyber

export MODULES_INSTALL_PATH=$TOOL_BASE_PATH/../bin/modules
echo MODULES_INSTALL_PATH = $TOOL_BASE_PATH/../bin/modules

export THIRD_LIBRARY_INSTALL_PATH=$TOOL_BASE_PATH/../bin/library
echo THIRD_LIBRARY_INSTALL_PATH = $TOOL_BASE_PATH/../bin/library

cd $APOLLO_BUILD_ENV_DIR


export PATH="$PATH:$PYTHON_BIN_PATH"

export BOOST_ROOT="$TOOL_BASE_PATH/Boost-1.78.0" 
export BOOST_INCLUDEDIR="$BOOST_ROOT/build/linux-x86/include"
export BOOST_LIBRARYDIR="$BOOST_ROOT/build/linux-x86/lib"
export PATH="$PATH:$BOOST_ROOT"
export CPATH="$CPATH:$BOOST_INCLUDEDIR"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:BOOST_LIBRARYDIR"


#apollo key world setting......
export DOWNLOAD_LOG="$APOLLO_BUILD_ENV_DIR/build.log"
echo DOWNLOAD_LOG = $DOWNLOAD_LOG

export LOCAL_HTTP_ADDR="http://172.17.0.1:8388"
echo LOCAL_HTTP_ADDR = $LOCAL_HTTP_ADDR

export WORKHORSE="gpu"
echo "WORKHORSE is: " ${WORKHORSE} 

export INSTALL_MODE="download" #build download
echo "INSTALL_MODE is: " ${INSTALL_MODE}

export nproc="32"
echo "make -j is: 32"

#do cyber and apollo patch here


