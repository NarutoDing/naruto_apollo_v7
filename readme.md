# General

This is an open source project made by **Jiangang Ding**.

The purpose of this project is to automatically compile Apollo project.

 My goal is to create cross platform compilation scripts，such as ubuntu、nvidia-orin paltform and so on, please contribute your ideas.

Any contribution is welcome.

If you find any bugs, please submit your issue.

 **WeChat**: 13052288554



# Introduction to project catalogue 

**----naruto_apollo_v7**    root path

​    **----bin**    Installation location of all library files and header files, including third-party libraries

​        ----cyber

​        ----library

​        ----modules

​    **----build**   Apollo compilation information 

​    **----cmake**  Apollo compilation tools and thirdparty cmake include

​    **----CMakeLists.txt**  root cmakelist

​    **----cyber**   apollo cyber

​    **----modules**  apollo modules

​    **----readme.md**  follow this to run apollo

​    **----tools**   apollo build env

​        ----ApolloBuildEnv

​        ----Cmake-3.20.5

​        ----Python-3.9.5

​        ----thirdparty  

​     

# How to

-  Please put the naruto_apollo_v7 project in the home directory 
- cd   ${**home**}/naruto_apollo_v7/tools/ApolloBuildEnv
- source  ./ApolloEnvHostLinux.sh
- python3.9 create_apollo_cmakelist.py
- python3.9 create_proto_cmakelist.py
- cd  ../../
- python3.9 cmake/apollo_build_script.py  -p host-linux >  /home/naruto/naruto_apollo_v7/trace.log 2>&1

 If you don't want to recompile ,please run the follow command:

- python3.9 cmake/apollo_build_script.py  -m -p host-linux >  /home/naruto/naruto_apollo_v7/trace.log 2>&1

## For cyber 

**add**  -latomic  **in** cyber/croutine/CMakeLists.txt**------>**target_link_libraries(cyber_croutine_croutine)

**add** -lrt  **in** cyber/CMakeLists.txt**------>**target_link_libraries(cyber_cyber_core) **and** cyber/transport/shm/CMakeLists.txt**------>**target_link_libraries(cyber_transport_shm_posix_segment)

**add** -ldl **in** cyber/class_loader/shared_library/CMakeLists.txt**------>**target_link_libraries(cyber_class_loader_shared_library_shared_library)

**add** detail/swap_x86_64.S **in** cyber/croutine/CMakeLists.txt**------>**add_library(cyber_croutine_swap  SHARED)

## **For cyber bug**

**add** cyber::service_discovery::role  **in** cyber/service_discovery/CMakeLists.txt**------>**target_link_libraries(cyber_service_discovery_warehouse_base)

set_target_properties(testFunc_shared PROPERTIES OUTPUT_NAME "testFunc")



## For modules bug

- modules/drivers/lidar/hesai/driver/BUILD  modules/drivers/lidar/robosense/driver/BUILD   **------>** "//modules/drivers/lidar/proto:config_cc_proto",

- modules/drivers/lidar/velodyne/driver/BUILD **------>** "//modules/drivers/lidar/proto:config_cc_proto",

- modules/drivers/lidar/robosense/driver/BUILD  **------>**"//modules/drivers/lidar/proto:robosense_cc_proto",

- modules/drivers/lidar/common/driver_factory/BUILD **------>**"//modules/drivers/lidar/proto:config_cc_proto", **and** "//modules/drivers/lidar/proto:lidar_parameter_cc_proto",
