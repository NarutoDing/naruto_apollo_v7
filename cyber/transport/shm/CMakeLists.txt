cmake_minimum_required(VERSION 3.16)

project(cyber_transport_shm)
message("${Green} [info] cyber_transport_shm cmakelist ${ColourReset}")

add_library(cyber_transport_shm_block  SHARED
  block.cc
)
set_target_properties(cyber_transport_shm_block  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_block
  cyber::base::atomic_rw_lock
  cyber::common::log
)
add_library(cyber::transport::shm::block  ALIAS   cyber_transport_shm_block)

add_library(cyber_transport_shm_condition_notifier  SHARED
  condition_notifier.cc
)
set_target_properties(cyber_transport_shm_condition_notifier  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_condition_notifier
  cyber::transport::shm::notifier_base
  cyber::common::global_data
  cyber::common::log
  cyber::common::util
)
add_library(cyber::transport::shm::condition_notifier  ALIAS   cyber_transport_shm_condition_notifier)

add_library(cyber_transport_shm_multicast_notifier  SHARED
  multicast_notifier.cc
)
set_target_properties(cyber_transport_shm_multicast_notifier  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_multicast_notifier
  cyber::transport::shm::notifier_base
  cyber::common::global_data
  cyber::common::log
  cyber::common::macros
)
add_library(cyber::transport::shm::multicast_notifier  ALIAS   cyber_transport_shm_multicast_notifier)

set(virtual_cc  $ENV{TOOL_BASE_PATH}/ApolloBuildEnv/virtual_cc.cc)
add_library(cyber_transport_shm_notifier_base  SHARED
  ${virtual_cc}
  notifier_base.h
)
set_target_properties(cyber_transport_shm_notifier_base  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_notifier_base
  cyber::transport::shm::readable_info
)
add_library(cyber::transport::shm::notifier_base  ALIAS   cyber_transport_shm_notifier_base)

add_library(cyber_transport_shm_notifier_factory  SHARED
  notifier_factory.cc
)
set_target_properties(cyber_transport_shm_notifier_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_notifier_factory
  cyber::transport::shm::condition_notifier
  cyber::transport::shm::multicast_notifier
  cyber::transport::shm::notifier_base
  cyber::common::global_data
  cyber::common::log
)
add_library(cyber::transport::shm::notifier_factory  ALIAS   cyber_transport_shm_notifier_factory)

add_library(cyber_transport_shm_readable_info  SHARED
  readable_info.cc
)
set_target_properties(cyber_transport_shm_readable_info  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_readable_info
  cyber::common::log
)
add_library(cyber::transport::shm::readable_info  ALIAS   cyber_transport_shm_readable_info)

add_library(cyber_transport_shm_xsi_segment  SHARED
  xsi_segment.cc
)
set_target_properties(cyber_transport_shm_xsi_segment  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_xsi_segment
  cyber::transport::shm::segment
  cyber::common::log
  cyber::common::util
)
add_library(cyber::transport::shm::xsi_segment  ALIAS   cyber_transport_shm_xsi_segment)

add_library(cyber_transport_shm_posix_segment  SHARED
  posix_segment.cc
)
set_target_properties(cyber_transport_shm_posix_segment  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_posix_segment
  -lrt
  cyber::transport::shm::segment
  cyber::common::log
  cyber::common::util
)
add_library(cyber::transport::shm::posix_segment  ALIAS   cyber_transport_shm_posix_segment)

add_library(cyber_transport_shm_segment  SHARED
  segment.cc
)
set_target_properties(cyber_transport_shm_segment  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_segment
  cyber::transport::shm::block
  cyber::transport::shm::shm_conf
  cyber::transport::shm::state
  cyber::common::log
  cyber::common::util
)
add_library(cyber::transport::shm::segment  ALIAS   cyber_transport_shm_segment)

add_library(cyber_transport_shm_segment_factory  SHARED
  segment_factory.cc
)
set_target_properties(cyber_transport_shm_segment_factory  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_segment_factory
  cyber::transport::shm::posix_segment
  cyber::transport::shm::segment
  cyber::transport::shm::xsi_segment
  cyber::common::global_data
  cyber::common::log
)
add_library(cyber::transport::shm::segment_factory  ALIAS   cyber_transport_shm_segment_factory)

add_library(cyber_transport_shm_shm_conf  SHARED
  shm_conf.cc
)
set_target_properties(cyber_transport_shm_shm_conf  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cyber_transport_shm_shm_conf
  cyber::common::log
)
add_library(cyber::transport::shm::shm_conf  ALIAS   cyber_transport_shm_shm_conf)

add_library(cyber_transport_shm_state  SHARED
  state.cc
)
set_target_properties(cyber_transport_shm_state  PROPERTIES LINKER_LANGUAGE CXX)

add_library(cyber::transport::shm::state  ALIAS   cyber_transport_shm_state)

