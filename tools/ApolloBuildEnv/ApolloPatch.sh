#! /bin/sh
#set -x
#set -e

cat << End-of-msg
------------------------------------------------------------------------------
This is an Apollo compiled patch file
I will delete this file in the future and update the patch in the python file
------------------------------------------------------------------------------
End-of-msg


cyber_time_time="cyber::time::time"
replace_cyber_time_time="cyber::time::time"
sudo sed -i "s/$cyber_time_time/$replace_cyber_time_time\n  "-latomic"/g" "$NARUTO_APOLLO_ROOT/cyber/croutine/CMakeLists.txt"

cyber_core_lrt="cyber::transport::rtps::sub_listener"
replace_cyber_core_lrt="cyber::transport::rtps::sub_listener"
sudo sed -i "s/$cyber_core_lrt/$replace_cyber_core_lrt\n  "-lrt"/g" "$NARUTO_APOLLO_ROOT/cyber/CMakeLists.txt"

cyber_transport_lrt="target_link_libraries(cyber_transport_shm_posix_segment"
replace_cyber_transport_lrt="target_link_libraries(cyber_transport_shm_posix_segment"
sudo sed -i "s/$cyber_transport_lrt/$replace_cyber_transport_lrt\n  "-lrt"/g" "$NARUTO_APOLLO_ROOT/cyber/transport/shm/CMakeLists.txt"

cyber_class_loader_ldl="target_link_libraries(cyber_class_loader_shared_library_shared_library"
replace_cyber_class_loader_ldl="target_link_libraries(cyber_class_loader_shared_library_shared_library"
sudo sed -i "s/$cyber_class_loader_ldl/$replace_cyber_class_loader_ldl\n  "-ldl"/g" "$NARUTO_APOLLO_ROOT/cyber/class_loader/shared_library/CMakeLists.txt"

cyber_swap="add_library(cyber_croutine_swap  SHARED"
replace_cyber_swap="add_library(cyber_croutine_swap  SHARED"
replace_content="detail\/swap_x86_64.S"
sudo sed -i "s/$cyber_swap/$replace_cyber_swap\n  $replace_content/g" "$NARUTO_APOLLO_ROOT/cyber/croutine/CMakeLists.txt"

cyber_service_discovery="target_link_libraries(cyber_service_discovery_warehouse_base"
replace_cyber_service_discovery="target_link_libraries(cyber_service_discovery_warehouse_base"
replace_content_1="cyber::service_discovery::role"
sudo sed -i "s/$cyber_service_discovery/$replace_cyber_service_discovery\n  $replace_content_1/g" "$NARUTO_APOLLO_ROOT/cyber/service_discovery/CMakeLists.txt"
