cmake_minimum_required(VERSION 3.16)

project(modules_contrib_lgsvl_msgs_proto)
message("${Green} [info] modules_contrib_lgsvl_msgs_proto cmakelist ${ColourReset}")
include($ENV{TOOL_BASE_PATH}/../cmake/ProtoBuf.cmake)
file(GLOB proto_files LIST_DIRECTORIES false $ENV{NARUTO_APOLLO_ROOT}/modules/contrib/lgsvl_msgs/proto/*.proto)
list(LENGTH  proto_files  length)
if(${length} GREATER 0)
  naruto_apollo_protobuf_generate_cpp_py(${CMAKE_CURRENT_SOURCE_DIR} proto_srcs proto_hdrs proto_python ${proto_files})
endif()

add_library(modules_contrib_lgsvl_msgs_proto_detection3darray_cc_proto  SHARED
  detection3darray.pb.cc
)
set_target_properties(modules_contrib_lgsvl_msgs_proto_detection3darray_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_contrib_lgsvl_msgs_proto_detection3darray_cc_proto
  modules::contrib::lgsvl_msgs::proto::detection3d_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::contrib::lgsvl_msgs::proto::detection3darray_cc_proto  ALIAS   modules_contrib_lgsvl_msgs_proto_detection3darray_cc_proto)

add_library(modules_contrib_lgsvl_msgs_proto_detection2d_cc_proto  SHARED
  detection2d.pb.cc
)
set_target_properties(modules_contrib_lgsvl_msgs_proto_detection2d_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_contrib_lgsvl_msgs_proto_detection2d_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::contrib::lgsvl_msgs::proto::detection2d_cc_proto  ALIAS   modules_contrib_lgsvl_msgs_proto_detection2d_cc_proto)

add_library(modules_contrib_lgsvl_msgs_proto_detection2darray_cc_proto  SHARED
  detection2darray.pb.cc
)
set_target_properties(modules_contrib_lgsvl_msgs_proto_detection2darray_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_contrib_lgsvl_msgs_proto_detection2darray_cc_proto
  modules::contrib::lgsvl_msgs::proto::detection2d_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::contrib::lgsvl_msgs::proto::detection2darray_cc_proto  ALIAS   modules_contrib_lgsvl_msgs_proto_detection2darray_cc_proto)

add_library(modules_contrib_lgsvl_msgs_proto_detection3d_cc_proto  SHARED
  detection3d.pb.cc
)
set_target_properties(modules_contrib_lgsvl_msgs_proto_detection3d_cc_proto  PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(modules_contrib_lgsvl_msgs_proto_detection3d_cc_proto
  modules::contrib::lgsvl_msgs::proto::detection2d_cc_proto
  modules::common::proto::geometry_cc_proto
  modules::common::proto::header_cc_proto
)
add_library(modules::contrib::lgsvl_msgs::proto::detection3d_cc_proto  ALIAS   modules_contrib_lgsvl_msgs_proto_detection3d_cc_proto)

