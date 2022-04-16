# General

This is an open source project made by **Jiangang Ding**.

The purpose of this project is to automatically compile Apollo project.

 My goal is to create cross platform compilation scripts，such as ubuntu、nvidia-orin paltform and so on, please contribute your ideas.

Any contribution is welcome.

If you find any bugs, please submit your issue.

 **WeChat**: 13052288554



# Introduction to project catalogue 

**--naruto_apollo_v7**    root path

​			**--bin**    Installation location of all library files and header files, including third-party libraries

​            				--cyber

​            				--library

​           				 --modules

​			**--build**   Apollo compilation information 

​			**--cmake**  Apollo compilation tools and thirdparty cmake include

​			 **--CMakeLists.txt**  root cmakelist

​			 **--cyber**   apollo cyber

​			**--modules**  apollo modules

​			**--readme.md**  follow this to run apollo

​			**--tools**   apollo build env

​            				--ApolloBuildEnv

​          				 --Cmake-3.20.5

​           				--Python-3.9.5

​           				--thirdparty  

​     

# How to

-  Please put the naruto_apollo_v7 project in the home directory 
- cd   ${**home**}/naruto_apollo_v7/tools/ApolloBuildEnv
- source  ./ApolloEnvHostLinux.sh
- python3.9 create_apollo_cmakelist.py
- python3.9 create_proto_cmakelist.py
- source ./ApolloPatch.sh
- cd  ../../
- python3.9 cmake/apollo_build_script.py  -p host-linux >  /home/naruto/naruto_apollo_v7/trace.log 2>&1

 **If you don't want to recompile ,please run the follow command:**

- python3.9 cmake/apollo_build_script.py  -m -p host-linux >  /home/naruto/naruto_apollo_v7/trace.log 2>&1



## **For cyber bug**

Currently i use the ApolloPatch.sh file to solve some bug, it will be solved later in the create_apollo_cmakelist.py script

## For modules bug

- /home/naruto/naruto_apollo_v7/modules/map/tools/map_datachecker/client/CMakeLists.txt --->collection_service_cc_grpc replace by collection_service_cc_proto
- /home/naruto/naruto_apollo_v7/modules/map/tools/map_datachecker/server/CMakeLists.txt --->collection_service_cc_grpc replace by collection_service_cc_proto

## For QT setting

In QT **Build Environment**, click **Batch Edit** button, add the following message by your own environment

```
APOLLO_BUILD_ENV_DIR=/home/naruto/naruto_apollo_v7/tools/ApolloBuildEnv
CMAKE_BIN_PATH="/home/naruto/naruto_apollo_v7/tools/Cmake-3.20.5/bin/cmake"
CYBER_INSTALL_PATH=/home/naruto/naruto_apollo_v7/bin/cyber
MODULES_INSTALL_PATH=home/naruto/naruto_apollo_v7/bin/modules
NARUTO_APOLLO_ROOT=/home/naruto/naruto_apollo_v7
THIRD_LIBRARY_INSTALL_PATH=/home/naruto/naruto_apollo_v7/bin/library
THIRD_PARTY_PATH="${TOOL_BASE_PATH}/thirdparty"
TOOL_BASE_PATH=/home/naruto/naruto_apollo_v7/tools
```

